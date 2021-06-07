#pragma once

enum GenLanguageType
{
    LUA     = 1,
    JSON    = 2,
    CSHARP  = 3,
};

struct ConfigOptions
{
    ConfigOptions()
        : gen_server_path{}, gen_client_path{}, gen_local_path{}
    {}

    QString data_path;
    QString gen_server_path;
    QString gen_client_path;
    QString gen_local_path;
    QString name_filters;
};