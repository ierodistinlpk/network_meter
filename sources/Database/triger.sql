
CREATE OR REPLACE FUNCTION "create_result" () RETURNS trigger AS
'
declare
idcycle int;
idprobe int8;
idsession int;
timm timestamp;
BEGIN
   idcycle:=NEW.cycle_num;
idprobe:=NEW.ID_PROBE;
idsession:=NEW.ID_SESSION;
timm:=currENT_TIMESTAMP;
if (select cycle from result where "ID_PROBE"=idprobe AND "ID_SESSION"=idsession AND cycle = idcycle) is null then 
    insert into result (cycle,timestmp, "ID_PROBE", "ID_SESSION")values (idcycle, timm, idprobe, idsession);
end if;
return NEW;  
END;
'
language "plpgsql";


CREATE OR REPLACE FUNCTION "createupd_result" () RETURNS trigger AS
'
declare
idcycle int;
idprobe int8;
idsession int;
BEGIN
idcycle:=NEW.cycle;
idprobe:=NEW."ID_PROBE";
idsession:=NEW."ID_SESSION";
if (select cycle from result where "ID_PROBE"=idprobe AND "ID_SESSION"=idsession AND cycle = idcycle) is not null then 
    update result set timestmp=NEW.timestmp where "ID_PROBE"=idprobe AND "ID_SESSION"=idsession AND cycle = idcycle;
	return NULL;
end if;
return NEW;

END;
'
language "plpgsql";


create trigger upd_result before insert on result for each row
execute procedure  "createupd_result"();



create trigger ins_checker before insert on event FOR EACH ROW
execute procedure create_result();

