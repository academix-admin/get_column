EXTENSION = get_column
MODULES = get_column
DATA = get_column--1.0.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
