#include <string>
#include <miniocpp/client.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdexcept>

using minio::s3::Client;
using minio::s3::BaseUrl;
using minio::s3::MakeBucketArgs;
using minio::s3::BucketExistsArgs;
using minio::s3::ListObjectsResult;
using minio::s3::ListObjectsArgs;
using minio::s3::Item;
using minio::creds::StaticProvider;

using std::string;
using std::make_unique;
using std::make_shared;
using std::unique_ptr;
using std::shared_ptr;
using std::runtime_error;

namespace py = pybind11;
