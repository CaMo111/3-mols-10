// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/dynamic_quicklex.h"

BUILD_CT(CT_QUICK_LEXLESS, 2)
#include "minion.h"
#include "../../minion/constraints/dynamic_vecneq.h"

BUILD_CT(CT_WATCHED_VECNEQ, 2)
#include "minion.h"
#include "../../minion/constraints/dynamic_vecneq.h"

BUILD_CT(CT_WATCHED_VEC_OR_LESS, 2)
#include "minion.h"
#include "../../minion/constraints/dynamic_sumor.h"

BUILD_CT(CT_WATCHED_HAMMING, 2)
#include "minion.h"
#include "../../minion/constraints/dynamic_sumor.h"

BUILD_CT(CT_WATCHED_NOT_HAMMING, 2)
