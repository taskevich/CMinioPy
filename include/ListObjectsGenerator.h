#include "external.h"
#include "MinioApi.h"

class ListObjectsIterator {
public:
    ListObjectsIterator(Client* client, const ListObjectsArgs& args)
        : client_(client), response_(client->ListObjects(args)) {}

    py::dict next() {
        while (response_) {
            const Item& item = *response_;
            ++response_;
            if (item.name.empty() || item.name.back() == '/')
                continue;
            py::dict py_dict;
            py_dict["name"] = item.name;
            py_dict["size"] = item.size;
            py_dict["last_modified"] = item.last_modified.ToISO8601UTC();
            return py_dict;
        }
        throw py::stop_iteration();
    }

private:
    Client* client_;
    ListObjectsResult response_;
};
