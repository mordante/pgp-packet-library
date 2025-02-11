#pragma once

#include "eddsa_public_key.h"


namespace pgp {

    /**
     *  Class for working with an EdDSA secret key
     */
    class eddsa_secret_key
    {
        public:
            /**
             *  Constructor
             *
             *  @param  parser  The decoder to parse the data
             */
            eddsa_secret_key(decoder &parser);

            /**
             *  Constructor
             *
             *  @param  k           The secret scalar for the public point
             */
            eddsa_secret_key(multiprecision_integer k) noexcept;

            /**
             *  Comparison operators
             *
             *  @param  other   The object to compare with
             */
            bool operator==(const eddsa_secret_key &other) const noexcept;
            bool operator!=(const eddsa_secret_key &other) const noexcept;

            /**
             *  Determine the size used in encoded format
             *  @return The number of bytes used for encoded storage
             */
            size_t size() const noexcept;

            /**
             *  Retrieve the secret scalar
             *
             *  @return The secret scalar for the public point
             */
            const multiprecision_integer &k() const noexcept;

            /**
             *  Write the data to an encoder
             *
             *  @param  writer  The encoder to write to
             *  @throws std::out_of_range, std::range_error
             */
            template <class encoder_t>
            void encode(encoder_t &writer) const
            {
                // encode the secret key
                _k.encode(writer);
            }
        private:
            multiprecision_integer  _k;     // the secret scalar for the public point
    };

}
