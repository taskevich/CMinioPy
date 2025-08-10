#include "external.h"
#include "MinioApi.h"

PYBIND11_MODULE(cminiopy, m) {
    m.doc() = "Minio-cpp client wrapper";

    py::class_<CMinio, py::smart_holder>(m, "CMinio")
        .def(py::init<const std::string&, const std::string&, const std::string&, bool>(),
             py::arg("endpoint"), py::arg("access_key"),
             py::arg("secret_key"), py::arg("secure") = true)
        .def("bucket_exists", &CMinio::bucket_exists)
        .def("make_bucket", &CMinio::make_bucket)
        .def("list_objects", [](CMinio &self, const std::string &bucket, const std::string &prefix, bool recursive) {
            ListObjectsArgs args;
            args.bucket = bucket;
            if (!prefix.empty())
                args.prefix = prefix;
            args.recursive = recursive;
            return std::make_shared<ListObjectsIterator>(self.client_.get(), args);
        });

    py::class_<ListObjectsIterator, std::shared_ptr<ListObjectsIterator>>(m, "ListObjectsIterator")
        .def(py::init<Client*, const ListObjectsArgs&>())
        .def("__iter__", [](ListObjectsIterator &it) -> ListObjectsIterator& { return it; })
        .def("__next__", &ListObjectsIterator::next);
}
