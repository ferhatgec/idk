#pragma once

#include "../types/predefined.hpp"
#include "sort_base.hpp"
#include <utility>

namespace idk {
template<typename Type>
class InsertionSort : public SortBase<Type> {
public:
    InsertionSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    InsertionSort(Vec<Type>&& vec) noexcept {
        this->_vec = std::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_insertionsort(comp);
    }
private:
    template<typename Compare>
    void
    _insertionsort(Compare comp) noexcept {
        isize index = 1;

        while(index < this->_vec.size()) {
            isize j = index;

            while(j > 0 && !comp(this->_vec.at_without_check(j - 1), this->_vec.at_without_check(j))) {
                auto _temp = this->_vec.at_without_check(j),
                     _temp2= this->_vec.at_without_check(j - 1);

                (void)this->_vec.change_val_at_index(j, _temp2);
                (void)this->_vec.change_val_at_index(j - 1, _temp);

                --j;
            }

            ++index;
        }
    }
};
} // namespace idk