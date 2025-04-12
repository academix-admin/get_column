CREATE FUNCTION get_column(record, text)
RETURNS anyelement
AS 'MODULE_PATHNAME', 'get_column'
LANGUAGE C STRICT;

COMMENT ON FUNCTION get_column(record, text) IS 'Returns the value of a column from a row';
