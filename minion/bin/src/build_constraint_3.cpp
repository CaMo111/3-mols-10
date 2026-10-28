// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/sum_constraints/constraint_sum.h"

BUILD_CT(CT_WEIGHTLEQSUM, 2)
#include "minion.h"
#include "../../minion/constraints/check_assign.h"

BUILD_CT(CT_CHECK_ASSIGN, 0)
#include "minion.h"
#include "../../minion/constraints/check_gsa.h"

BUILD_CT(CT_CHECK_GSA, 0)
#include "minion.h"
#include "../../minion/constraints/forward_checking.h"

BUILD_CT(CT_FORWARD_CHECKING, 0)
#include "minion.h"
#include "../../minion/constraints/reify.h"

BUILD_CT(CT_REIFY, 1)
