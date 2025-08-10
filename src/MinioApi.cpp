#include "MinioApi.h"
#include <chrono>

CMinio::CMinio(
    const string& endpoint,
    const string& access_key,
    const string& secret_key,
    bool secure
)
    : base_url_(endpoint, secure) {
    creds_ = make_unique<StaticProvider>(access_key, secret_key);
    client_ = make_unique<Client>(base_url_, creds_.get());
}

bool CMinio::bucket_exists(const string& bucket_name) {
    BucketExistsArgs args;
    args.bucket = bucket_name;
    auto resp = client_->BucketExists(args);
    return resp.exist;
}

bool CMinio::make_bucket(const string& bucket_name) {
    MakeBucketArgs args;
    args.bucket = bucket_name;
    auto resp = client_->MakeBucket(args);

    if (!resp) {
        throw runtime_error(resp.Error().String());
    }
    return true;
}

py::list CMinio::list_objects(const string& bucket_name, const string& prefix) {
    ListObjectsArgs args;
    args.bucket = bucket_name;
    if (!prefix.empty())
        args.prefix = prefix;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    auto resp = client_->ListObjects(args);
    py::list py_list;
    for (; resp; resp++) {
        const Item& item = *resp;

        if (!item || item.name.back() == '/')
            continue;

        py::dict py_dict;
        py_dict["name"] = item.name;
        py_dict["size"] = item.size;
        py_dict["last_modified"] = item.last_modified.ToISO8601UTC();
        py_list.append(py_dict);
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    printf("Elapsed time: %d", std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count());
    return py_list;
}
