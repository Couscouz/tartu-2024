FROM php:7.4-apache

RUN apt update && apt install -y tcl-expect-dev unzip \
    && apt install sqlite3

RUN pecl install expect \
    && docker-php-ext-enable expect

RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer
RUN composer require "twig/twig:^3.0"

RUN mkdir /data
COPY blog.db /data/blog.db
RUN chown -R www-data:www-data /data

RUN sqlite3 /data/blog.db "INSERT INTO USERS (id, username, password, isadmin) VALUES \
    (1, 'admin', '$(cat /dev/urandom | base64 | head -c 20)', 1), \
    (2, 'user',  '$(cat /dev/urandom | base64 | head -c 20)', 0)"

RUN mkdir /var/www/html/uploads
RUN chown -R www-data:www-data /var/www/html/uploads

COPY /src /var/www/html