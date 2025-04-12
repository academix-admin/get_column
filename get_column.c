#include "postgres.h"
#include "fmgr.h"
#include "utils/lsyscache.h"
#include "utils/typcache.h"
#include "utils/builtins.h"
#include "access/htup_details.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(get_column);

Datum
get_column(PG_FUNCTION_ARGS)
{
    HeapTupleHeader rec = PG_GETARG_HEAPTUPLEHEADER(0);
    text *column_name_text = PG_GETARG_TEXT_PP(1);
    char *column_name = text_to_cstring(column_name_text);

    Oid tup_type = HeapTupleHeaderGetTypeId(rec);
    int32 tup_typmod = HeapTupleHeaderGetTypMod(rec);

    TupleDesc tupdesc = lookup_rowtype_tupdesc(tup_type, tup_typmod);
    HeapTupleData tuple;
    tuple.t_len = HeapTupleHeaderGetDatumLength(rec);
    tuple.t_data = rec;

    for (int i = 0; i < tupdesc->natts; i++)
    {
        Form_pg_attribute attr = TupleDescAttr(tupdesc, i);
        if (attr->attisdropped || attr->attnum < 1)
            continue;

        // Case-insensitive comparison
        if (pg_strcasecmp(NameStr(attr->attname), column_name) == 0)
        {
            Datum val;
            bool isnull;
            val = heap_getattr(&tuple, attr->attnum, tupdesc, &isnull);
            ReleaseTupleDesc(tupdesc);
            if (isnull)
                PG_RETURN_NULL();
            PG_RETURN_DATUM(val);
        }
    }

    ReleaseTupleDesc(tupdesc);
    ereport(ERROR, (errmsg("column \"%s\" does not exist", column_name)));
    PG_RETURN_NULL(); // Not reached
}
