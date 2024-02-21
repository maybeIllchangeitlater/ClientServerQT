-- Создание базы данных
CREATE DATABASE test;

-- Подключение к созданной базе данных
\c test;

DO $$
BEGIN
    RAISE NOTICE 'Initializing the database...';
END $$;

-- Удаление представления, если оно уже существует
DROP VIEW IF EXISTS custom_view;

-- Удаление таблиц, если они уже существуют
DROP TABLE IF EXISTS string_data CASCADE;
DROP TABLE IF EXISTS json_data CASCADE;
DROP TABLE IF EXISTS binary_data CASCADE;

-- Удаление последовательностей, если они уже существуют
DROP SEQUENCE IF EXISTS string_data_id_seq;
DROP SEQUENCE IF EXISTS json_data_id_seq;
DROP SEQUENCE IF EXISTS binary_data_id_sq;

-- Создание последовательности для автоинкремента id для string_data
CREATE SEQUENCE string_data_id_seq START 1;

-- Создание последовательности для автоинкремента id для json_data
CREATE SEQUENCE json_data_id_seq START 1;

-- Создание последовательности для автоинкремента id для binary_data
CREATE SEQUENCE binary_data_id_seq START 1;

-- Создание таблицы для хранения строковых данных
CREATE TABLE string_data (
    id INT PRIMARY KEY DEFAULT nextval('string_data_id_seq'),
    text VARCHAR(255),
    received_date DATE DEFAULT NULL,
    received_time TIME DEFAULT NULL
);

-- Создание таблицы для хранения JSON данных
CREATE TABLE json_data (
    id INT PRIMARY KEY DEFAULT nextval('json_data_id_seq'),
    name VARCHAR(255),
    gen_id VARCHAR(255),
    number VARCHAR(255),
    created_date DATE,
    created_time TIME,
    received_date DATE DEFAULT NULL,
    received_time TIME DEFAULT NULL
);

-- Создание таблицы для хранения бинарных данных
CREATE TABLE binary_data (
    id INT PRIMARY KEY DEFAULT nextval('binary_data_id_seq'),
    data BYTEA,
    received_date DATE DEFAULT NULL,
    received_time TIME DEFAULT NULL
);

-- Создание функции для обновления даты и времени приема данных
CREATE OR REPLACE FUNCTION update_received_datetime()
RETURNS TRIGGER AS $$
BEGIN
    NEW.received_date := CURRENT_DATE;
    NEW.received_time := CURRENT_TIME;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- Создание триггера для таблицы string_data
CREATE TRIGGER update_string_data_datetime_trigger
BEFORE INSERT ON string_data
FOR EACH ROW
EXECUTE FUNCTION update_received_datetime();

-- Создание триггера для таблицы json_data
CREATE TRIGGER update_json_data_datetime_trigger
BEFORE INSERT ON json_data
FOR EACH ROW
EXECUTE FUNCTION update_received_datetime();

-- Создание триггера для таблицы binary_data
CREATE TRIGGER update_binary_data_datetime_trigger
BEFORE INSERT ON binary_data
FOR EACH ROW
EXECUTE FUNCTION update_received_datetime();

-- Создание произвольного VIEW
CREATE VIEW custom_view AS
SELECT id, text, received_date
FROM string_data
UNION ALL
SELECT id, name, received_date
FROM json_data;

-- Создание пользователя для доступа к базе данных
CREATE USER test WITH PASSWORD 'test';
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO test;
GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO test;
GRANT ALL PRIVILEGES ON ALL FUNCTIONS IN SCHEMA public TO test;
