
create database test_petshop;
show databases;

show tables;

create table pet (
	name varchar(20),
    owner varchar(20),
    species varchar(20),
    sex char(1),
    birth date
);

show tables;

describe pet;

select * from pet;

insert into pet values ('초롱이', '이은비', '고양이', 'F', '2013-02-14');
insert into pet values ('초코', '안현주', '고양이', 'M', '2014-03-17');
insert into pet values ('은별이', '조영섭', '고양이', 'F', '2009-05-13');
insert into pet values ('백구', '김종훈', '개', 'M', '2010-08-24');
insert into pet values ('웅산', '신상을', '개', 'M', '2009-08-31');
insert into pet values ('길산', '신상을', '개', 'F', '2008-09-11');

select * from pet;
select * from pet where name='백구';
select * from pet where sex='F';
select * from pet where sex='M' and species='고양이';

select name, birth from pet;
select owner from pet where species='고양이';

select * from pet order by birth;
select * from pet order by birth desc;
