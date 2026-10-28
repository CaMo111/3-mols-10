// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/constraint_gccweak.h"

BUILD_CT(CT_GCCWEAK, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_gaclex.h"

BUILD_CT(CT_GACLEXLEQ, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_lex.h"

BUILD_CT(CT_LEXLEQ, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_lex.h"

BUILD_CT(CT_LEXLESS, 2)
#include "minion.h"
#include "../../minion/constraints/dynamic_quicklex.h"

BUILD_CT(CT_QUICK_LEXLEQ, 2)
