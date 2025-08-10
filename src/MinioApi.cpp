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
    client_ = make_shared<Client>(base_url_, creds_.get());
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

shared_ptr<ListObjectsIterator> CMinio::list_objects(const string& bucket_name, const string& prefix, bool recursive) {
    ListObjectsArgs args;
    args.bucket = bucket_name;
    if (!prefix.empty())
        args.prefix = prefix;
    args.recursive = recursive;
    return make_shared<ListObjectsIterator>(client_.get(), args);
}
