#pragma once

#include <string>
#include <miniocpp/client.h>
#include "external.h"

class CMinio : public py::trampoline_self_life_support {
public:
    CMinio(
        const string& endpoint,
        const string& access_key,
        const string& secret_key,
        bool secure
    );

    bool bucket_exists(const string& bucket_name);
    bool make_bucket(const string& bucket_name);
    py::list list_objects(const string& bucket_name, const string& prefix);
private:
    BaseUrl base_url_;
    unique_ptr<StaticProvider> creds_;
    unique_ptr<Client> client_;
};
