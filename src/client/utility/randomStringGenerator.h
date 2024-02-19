#ifndef CLIENTSERVERQT_CLIENT_UTILITY_RANDOMSTRINGGENERATOR_H_
#define CLIENTSERVERQT_CLIENT_UTILITY_RANDOMSTRINGGENERATOR_H_

#include <random>
#include <QString>

namespace test{
    class RandomStringGenerator{
        constexpr static const char charnumset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

     public:
        RandomStringGenerator()
            : _gen(std::random_device()()), _lengthDistribution(5, 50),
              _charNumDistribution(0, sizeof(charnumset) - 2), _charOnlyDistribution(9, sizeof(charnumset) - 2) {}

        /**
         * @brief generateNumCharString generates string consisting of random character and numbers with length 5-50
         * @return generated string
         */
        QString generateNumCharString() {
            return generateString(_charNumDistribution);
        }
        /**
         * @brief generateCharOnlyString generates string consisting of random character with length 5-50
         * @return generated string
         */
        QString generateCharOnlyString() {
            return generateString(_charOnlyDistribution);
        }


    private:
        /**
         * @brief generateString generates string based on charnumset and passed distribution
         * @param dist - from to, _charNumDistribution to include both characters and numbers,
         * _charOnlyDistribution for characters only
         * @return generated string
         */
        QString generateString(std::uniform_int_distribution<int> &dist){
            int length = dist(_gen);
            QString randString;
            randString.reserve(length);
            for (int i = 0; i < length; ++i) {
                    randString += charnumset[_charNumDistribution(_gen)];
            }
            return randString;
        }

        std::mt19937 _gen;
        std::uniform_int_distribution<int> _lengthDistribution;
        std::uniform_int_distribution<int> _charNumDistribution;
        std::uniform_int_distribution<int> _charOnlyDistribution;
    };
}

#endif //CLIENTSERVERQT_CLIENT_UTILITY_RANDOMSTRINGGENERATOR_H_
