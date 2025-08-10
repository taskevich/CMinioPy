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
        .def("list_objects", 
            [](CMinio &self, const std::string &a, const std::string &b) {
                return self.list_objects(a, b);
            },
            py::arg("bucket_name"), py::arg("prefix") = ""
        );
}
