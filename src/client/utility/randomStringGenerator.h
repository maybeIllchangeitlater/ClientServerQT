#ifndef CLIENTSERVERQT_CLIENT_UTILITY_RANDOMSTRINGGENERATOR_H_
#define CLIENTSERVERQT_CLIENT_UTILITY_RANDOMSTRINGGENERATOR_H_

#include <random>
#include <QString>

namespace test{
    class RandomStringGenerator{
        constexpr static const char CHARNUMSET[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        constexpr static const unsigned short MIN_STRING_LENGTH = 5;
        constexpr static const unsigned short MAX_STRING_LENGTH = 50;
        constexpr static const unsigned short NUMBERS_END_AFTER = 9;

     public:
        /**
         * @brief RandomStringGenerator создает объект класса предназначенного для генерации случайных строк
         */
        RandomStringGenerator()
            : _gen(std::random_device()()), _lengthDistribution(MIN_STRING_LENGTH, MAX_STRING_LENGTH),
              _charNumDistribution(0, sizeof(CHARNUMSET) - 2), _numOnlyDistribution(0, NUMBERS_END_AFTER) {}

        /**
         * @brief generateNumCharString генерирует строку из случайных латинских букв и цифр длинной 5-50
         * @return сгенерированная строку
         */
        QString generateNumCharString() {
            return generateString(_charNumDistribution);
        }
        /**
         * @brief generateCharOnlyString генерирует строку из случайных цифр длинной 5-50
         * @return сгенерированная строку
         */
        QString generateNumOnlyString() {
            return generateString(_numOnlyDistribution);
        }


    private:
        /**
         * @brief generateString генерирует строку основываясь на массиве латинский цифр и букв(CHARNUMSET) и пришедшую дистрибуцию
         * @param dist - дистрибуция(от минимума до максимума), _charNumDistribution для цифр и букв,
         * _charOnlyDistribution для цифр
         * @return сгенерированная строку
         */
        QString generateString(std::uniform_int_distribution<int> &dist){
            int length = dist(_gen);
            QString randString;
            randString.reserve(length);
            for (int i = 0; i < length; ++i) {
                    randString += CHARNUMSET[_charNumDistribution(_gen)];
            }
            return randString;
        }

        std::mt19937 _gen;
        std::uniform_int_distribution<int> _lengthDistribution;
        std::uniform_int_distribution<int> _charNumDistribution;
        std::uniform_int_distribution<int> _numOnlyDistribution;
    };
}

#endif //CLIENTSERVERQT_CLIENT_UTILITY_RANDOMSTRINGGENERATOR_H_
