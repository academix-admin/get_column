# get_column

[![PGXN version](https://badge.pgxn.org/version/get_column.svg)](https://pgxn.org/dist/get_column/)
[![PGXN downloads](https://badge.pgxn.org/downloads/get_column.svg)](https://pgxn.org/dist/get_column/)

> Dynamic column extraction from a PostgreSQL record using case-insensitive field names.

## 🧩 About

`get_column` is a PostgreSQL extension that allows you to dynamically extract a column value from a composite `record` using the column's name — case-insensitive. This is especially useful for writing generic SQL functions or utilities where column names are not known ahead of time.

## 📦 Installation

If you're using PostgreSQL locally and have `pgxn`:

```bash
pgxn install get_column
```

Or build manually:

```bash
git clone https://github.com/academix-admin/get_column.git
cd get_column
make
sudo make install
```

Then in your database:

```sql
CREATE EXTENSION get_column;
```

> Note: This extension requires PostgreSQL server access for the shared library installation. It's not available on hosted platforms like Supabase unless explicitly whitelisted.

## 🛠️ Usage

```sql
SELECT get_column(ROW(1, 'hello', 3.14)::record, 'col2');
-- Returns: 'hello'
```

Supports:

- Case-insensitive column names
- Any composite record
- Returns the column value as `text`

### Example: With custom record

```sql
CREATE TYPE person AS (
  id      integer,
  name    text,
  age     integer
);

SELECT get_column(ROW(101, 'Ada', 24)::person, 'Name');
-- Returns: 'Ada'
```

## 📚 Function Signature

```sql
get_column(record, column_name text) RETURNS text
```

- `record`: The composite row.
- `column_name`: The name of the column to extract, case-insensitively.
- **Returns**: The column value as text, or `NULL` if the column doesn't exist.

## 🔍 Use Cases

- Dynamic report generation
- Generic audit logging
- Introspection-based utilities
- Dynamic filtering in user-defined functions

## 🧪 Testing

Run:

```bash
make installcheck
```

Ensure you have `pg_regress` installed (part of PostgreSQL dev tools).

## 📄 License

This extension is licensed under the [PostgreSQL License](https://www.postgresql.org/about/licence/).

---

Made with ❤️ by [@yourdevaji](https://github.com/yourdevaji)  
Published on [PGXN](https://pgxn.org/dist/get_column/)
