#pragma once

#include "BaseElem.h"
class Driver;

class Statement : public BaseElem {
 public: static int ret_flag;
};

class LocalStatement : public Statement {};
