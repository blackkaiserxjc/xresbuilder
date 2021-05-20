#include <msgpack.hpp>

namespace kr
{
    namespace core
    {
        template <typename Stream>
        struct Packer<::msgpack::packer<Stream>>
        {
        public:
            explicit Packer(Stream &stream)
                :packer_(stream)
            {}

            Packer& pack(bool value)
            {
                if (value)
                {
                    packer_.pack_true();
                }
                else
                {
                    packer_.pack_false();
                }
                return *this;
            }

            Pcker& pack(std::int32_t value)
            {
                packer_.pack_int32(value);
                return *this;
            }

            Packer& pack(std::uint32_t value)
            {
                packer_.pack_uint32(value);
                return *this;
            }

            Packer& pack(std::int64_t value)
            {
                packer_.pack_int64(value);
                return *this
            }

            Packer& pack(std::uint64_t value)
            {
                packer_.pack_uint64(value);
                return *this
            }

            Packer& pack(double value)
            {
                packer_.pack_double(value);
                return *this;
            }

            Packer& pack(std::string_view value)
            {
                packer_.pack_str(static_cast<std::uint32_t>(value.size()));
                packer_.pack_str_body(value.c_str(), value.size());
                return *this;
            }

            Packer& pack_begin_array(std::string_view name, std::size_t size)
            {
                pack(name);
                packer_.pack_array(size);
                return *this;
            }

            Packer& pack_end_array()
            {
                return *this;
            }

            Packer& pack_begin_map(std::string_view name, std::size_t size)
            {
                pack(name);
                packer_.pack_map(size);
                return *this;
            }

            Packer& pack_end_map()
            {
                return *this;
            }
        private:
            ::msgpack::packer<Stream> packer_;
        };
    }
}

