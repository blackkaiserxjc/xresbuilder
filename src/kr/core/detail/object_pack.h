#pragma once

#include <exception>
#include <msgpack.hpp>

namespace kr {
namespace core {

template <typename Packer, typename Reader>
void pack_statement(Packer &packer, const Type &type, const Reader &reader) {
    if (IsPod(type.base_type)) {
        pack_pod(packer, type, reader);
    } else if(IsObject(type.base_type)) {
        pack_object(packer, type, reader);
    } else if(IsArray(type.base_type)) {
        pack_array(packer, type, reader);
    }
}

template <typename Packer, typename Reader>
void pack_pod(Packer &packer, const Type &type, const Reader &reader) {
    if (!(IsPod(type.base_type))) {
        throw std::runtime_error("invaild type.");
    } 
    switch (type.base_type) {
    case BASE_TYPE_BOOL: {
        reader.template to<bool>(
            [&packer](bool value) { packer.pack(value); },
            [] { throw "invaild_cast"; });
    } break;

    case BASE_TYPE_INT: {
        reader.template to<std::int64_t>(
            [&packer](std::int64_t value) { packer.pack(value); },
            [] { throw "invalid_cast"; });
    } break;

    case BASE_TYPE_FLOAT: {
        reader.template to<double>(
            [&packer](double value) { packer.pack(value); },
            [] { throw "invaild_cast"; });
    } break;

    case BASE_TYPE_STRING: {
        reader.template to<std::string>(
            [&packer](std::string value) { packer.pack(value); },
            [] { throw "invaild_cast"; });
    } break;
    }
}

template <typename Packer, typename Reader>
void pack_object(Packer &packer, const Type &type, const Reader &reader) {
    if (type.base_type != BASE_TYPE_OBJECT && type.obj_def) {
        throw std::runtime_error("invaild type.");
    }
    packer.pack_begin_map(type.obj_def->fields.Size());
    reader.visit_map([&packer, obj_def = type.obj_def](const Reader& key, const Reader& value) {
        if (key.type() != BASE_TYPE_INT) {
            throw std::runtime_error("map type not std::uint32_t");
        }
        auto index = key.template as<std::uint32_t>();
        if (index < 0 or index >= obj_def->fields.Size()) {
            throw std::out_of_range("index out of range");
        }
        auto one_field = obj_def->fields.vec[index];
        if (one_field && one_field->index == index) {
            packer.key(one_field->name);
            pack_statement(packer, one_field->value.type, value);
        }
    });
    packer.pack_end_map();
}

template <typename Packer, typename Reader>
void pack_array(Packer &packer, const Type &type, const Reader &reader) {
  if (type.base_type != BASE_TYPE_ARRAY) {
    throw std::runtime_error("invaild type.");
  }
  reader.visit_array(
        [&packer](std::size_t size) { 
            packer.pack_begin_array(size); 
        },
        [&packer, type](std::size_t index, const Reader &reader) {
            if (IsPod(type.element)) {
                pack_pod(packer, Type(type.element), reader);
            } else if (IsObject(type.element)) {
                pack_object(packer, Type(type.element, type.obj_def), reader);
            }
        });
    packer.pack_end_array();
}

template <typename Packer, typename Reader>
void pack_root_array(Packer& packer, const Type &type, const Reader &reader) {
    if (type.base_type != BASE_TYPE_ARRAY) {
        throw std::runtime_error("invaild type");
    }
    if (IsPod(type.element)) {
        pack_pod(packer, Type(type.element), reader);
    } else if (IsObject(type.element)) {
        pack_object(packer, Type(type.element, type.obj_def), reader);
    }
}

template <typename Packer, typename Reader>
void pack(Packer &packer, const Type &type, const Reader &reader) {
    if (IsPod(type.base_type)) {
        pack_pod(packer, type, reader);
    } else if(IsObject(type.base_type)) {
        pack_object(packer, type, reader);
    } else if(IsArray(type.base_type)) {
        pack_array(packer, type, reader);
    }
}

} // namespace core
} // namespace kr