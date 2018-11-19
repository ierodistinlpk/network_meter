------------------------------
-- pgDesigner 1.2.7
--
-- Project    : diplom
-- Date       : 06/10/2009 16:36:07.364
-- Description: 
------------------------------


-- Start Sequenza's declaration
DROP SEQUENCE IF EXISTS "event_ID_EVENT_seq" CASCADE;
CREATE SEQUENCE "event_ID_EVENT_seq" INCREMENT 1 MINVALUE 1 MAXVALUE 9223372036854775807 START 1 NO CYCLE;

DROP SEQUENCE IF EXISTS "event_type_id_type_seq" CASCADE;
CREATE SEQUENCE "event_type_id_type_seq" INCREMENT 1 MINVALUE 1 MAXVALUE 9223372036854775807 START 1 NO CYCLE;

DROP SEQUENCE IF EXISTS "probe_ID_PROBE_seq" CASCADE;
CREATE SEQUENCE "probe_ID_PROBE_seq" INCREMENT 1 MINVALUE 1 MAXVALUE 9223372036854775807 START 1 NO CYCLE;

DROP SEQUENCE IF EXISTS "session_ID_SESSION_seq" CASCADE;
CREATE SEQUENCE "session_ID_SESSION_seq" INCREMENT 1 MINVALUE 1 MAXVALUE 9223372036854775807 START 1 NO CYCLE;

-- End Sequenza's declaration

-- Start Procedura's declaration




-- End Procedura's declaration

--Start Tabella's declaration
dROP TABLE IF EXISTS "agent" CASCADE;
CREATE TABLE "agent" (
"name" character varying(256) NOT NULL,
"passkey" character varying(32) NOT NULL
) WITH OIDS;
ALTER TABLE "agent" ADD CONSTRAINT "agent_pk" PRIMARY KEY("name");


DROP TABLE IF EXISTS "event" CASCADE;
CREATE TABLE "event" (
"ID_EVENT" bigint NOT NULL DEFAULT nextval('"event_ID_EVENT_seq"'::regclass),
"timestp" timestamp without time zone NOT NULL,
"adress" inet NOT NULL,
"id_type" integer NOT NULL,
"cycle_num" integer NOT NULL DEFAULT '0',
"id_probe" bigint NOT NULL DEFAULT '0',
"id_session" integer NOT NULL DEFAULT '0'
) WITH OIDS;
ALTER TABLE "event" ADD CONSTRAINT "event_pk" PRIMARY KEY("ID_EVENT");

DROP TABLE IF EXISTS "event_type" CASCADE;
CREATE TABLE "event_type" (
"is_err" boolean NOT NULL,
"code" numeric NOT NULL,
"name" character varying(16) NOT NULL,
"id_type" integer NOT NULL DEFAULT nextval('event_type_id_type_seq'::regclass)
) WITH OIDS;
ALTER TABLE "event_type" ADD CONSTRAINT "event_type_pk" PRIMARY KEY("id_type");


DROP TABLE IF EXISTS "probe" CASCADE;
CREATE TABLE "probe" (
"ID_PROBE" bigint NOT NULL DEFAULT nextval('"probe_ID_PROBE_seq"'::regclass),
"P_COUNT" numeric NOT NULL,
"SIZE" numeric NOT NULL,
"INTERVAL" numeric NOT NULL,
"target" inet NOT NULL,
"name" character varying(256) NOT NULL
) WITH OIDS;
ALTER TABLE probe ADD CONSTRAINT "probe_pk" PRIMARY KEY("ID_PROBE");

DROP TABLE IF EXISTS "result" CASCADE;
CREATE TABLE "result" (
"cycle" numeric NOT NULL,
"timestmp" timestamp without time zone NOT NULL,
"ID_PROBE" bigint NOT NULL,
"ID_SESSION" integer NOT NULL
) WITH OIDS;
ALTER TABLE "result" ADD CONSTRAINT "result_pk" PRIMARY KEY("cycle","ID_PROBE","ID_SESSION");

DROP TABLE IF EXISTS "result_node" CASCADE;
CREATE TABLE "result_node" (
"number" numeric NOT NULL,
"rtt" integer NOT NULL,
"id_session" integer NOT NULL,
"id_probe" bigint NOT NULL,
"cycle_num" integer NOT NULL
) WITH OIDS;
ALTER TABLE "result_node" ADD CONSTRAINT "result_node_pk" PRIMARY KEY("number","id_session","id_probe","cycle_num");

DROP TABLE IF EXISTS "session" CASCADE;
CREATE TABLE "session" (
"ID_SESSION" integer NOT NULL DEFAULT nextval('"session_ID_SESSION_seq"'::regclass),
"start_time" timestamp without time zone NOT NULL,
"end_time" timestamp without time zone,
"next_seq" integer NOT NULL DEFAULT '0',
"time_seek" integer DEFAULT '0',
"name" character varying(256) NOT NULL
) WITH OIDS;
ALTER TABLE "session" ADD CONSTRAINT "session_pk" PRIMARY KEY("ID_SESSION");

DROP TABLE IF EXISTS "target" CASCADE;
CREATE TABLE "target" (
"adress" inet NOT NULL,
"has_agent" boolean NOT NULL,
"description" character varying(32)
) WITH OIDS;
ALTER TABLE "target" ADD CONSTRAINT "target_pk" PRIMARY KEY("adress");

-- End Tabella's declaration

-- Start Trigger's declaration
/*DROP TRIGGER IF EXISTS "ins_checker" ON "event" CASCADE;
CREATE TRIGGER "ins_checker" BEFORE INSERT ON "event" FOR EACH ROW EXECUTE PROCEDURE "create_result"();

DROP TRIGGER IF EXISTS "upd_result" ON "result" CASCADE;
CREATE TRIGGER "upd_result" BEFORE INSERT ON "result" FOR EACH ROW EXECUTE PROCEDURE "createupd_result"();
*/
-- End Trigger's declaration

-- Start Relazione's declaration
--ALTER TABLE "probe" DROP CONSTRAINT "probe_owner" CASCADE;
ALTER TABLE "probe" ADD CONSTRAINT "probe_owner" FOREIGN KEY ("name") REFERENCES "agent"("name") ON UPDATE RESTRICT ON DELETE RESTRICT;

--ALTER TABLE "session" DROP CONSTRAINT "session_owner" CASCADE;
ALTER TABLE "session" ADD CONSTRAINT "session_owner" FOREIGN KEY ("name") REFERENCES "agent"("name") ON UPDATE RESTRICT ON DELETE RESTRICT;

---ALTER TABLE "event" DROP CONSTRAINT "ev_type" CASCADE;
ALTER TABLE "event" ADD CONSTRAINT "ev_type" FOREIGN KEY ("id_type") REFERENCES "event_type"("id_type") ON UPDATE CASCADE ON DELETE RESTRICT;

--ALTER TABLE "result" DROP CONSTRAINT "Result_key" CASCADE;
ALTER TABLE "result" ADD CONSTRAINT "Result_key" FOREIGN KEY ("ID_PROBE") REFERENCES "probe"("ID_PROBE") ON UPDATE RESTRICT ON DELETE RESTRICT;

--ALTER TABLE "event" DROP CONSTRAINT "cycle_key" CASCADE;
ALTER TABLE "event" ADD CONSTRAINT "cycle_key" FOREIGN KEY ("id_probe","id_session","cycle_num") REFERENCES "result"("ID_PROBE","ID_SESSION","cycle") ON UPDATE RESTRICT ON DELETE RESTRICT;

--ALTER TABLE "result_node" DROP CONSTRAINT "cycle_n_key" CASCADE;
ALTER TABLE "result_node" ADD CONSTRAINT "cycle_n_key" FOREIGN KEY ("id_probe","id_session","cycle_num") REFERENCES "result"("ID_PROBE","ID_SESSION","cycle") ON UPDATE RESTRICT ON DELETE RESTRICT;

--ALTER TABLE "result" DROP CONSTRAINT "Result_fkey2" CASCADE;
ALTER TABLE "result" ADD CONSTRAINT "Result_fkey3" FOREIGN KEY ("ID_SESSION") REFERENCES "session"("ID_SESSION") ON UPDATE CASCADE ON DELETE RESTRICT;

--ALTER TABLE "probe" DROP CONSTRAINT "probe_target" CASCADE;
ALTER TABLE "probe" ADD CONSTRAINT "probe_target" FOREIGN KEY ("target") REFERENCES "target"("adress") ON UPDATE RESTRICT ON DELETE RESTRICT;

-- End Relazione's declaration

