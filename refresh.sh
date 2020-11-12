#!/bin/bash
cd /apps/cdr_loading
mongo -u "root" -p1cbtm0ngo --authenticationDatabase "admin" < refresh.js
echo "MONGODB REFRESHED!!!"
mysql -uroot -picbt123 MSISDN < refresh.sql
mysql -uroot -picbt123 CELLID -e"truncate MISSING_CELLID"
tbls=`mysql --skip-column-names -uroot -picbt123 LAC -e"show tables;"|grep L`
for t in $tbls
do
	mysql -uroot -picbt123 LAC -e"drop table $t"
done
echo "MYSQL REFRESHED!!!"
