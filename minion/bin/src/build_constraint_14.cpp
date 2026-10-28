// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/unary/dynamic_literal.h"

BUILD_CT(CT_WATCHED_LIT, 1)
#include "minion.h"
#include "../../minion/constraints/unary/dynamic_notliteral.h"

BUILD_CT(CT_WATCHED_NOTLIT, 1)
#include "minion.h"
#include "../../minion/constraints/unary/dynamic_inintervalset.h"

BUILD_CT(CT_WATCHED_ININTERVALSET, 1)
#include "minion.h"
#include "../../minion/constraints/unary/dynamic_inrange.h"

BUILD_CT(CT_WATCHED_INRANGE, 1)
#include "minion.h"
#include "../../minion/constraints/unary/dynamic_inset.h"

BUILD_CT(CT_WATCHED_INSET, 1)
