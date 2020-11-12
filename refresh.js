use CDR
db.dropDatabase()
use CDR
db.createCollection("DEFAULT")
db.DEFAULT.createIndex({"MSISDN":1})
db.createCollection("FWD_CALL")
db.FWD_CALL.createIndex({"MSISDN":1})
db.createCollection("MCF_CALL")
db.MCF_CALL.createIndex({"MSISDN":1})
db.createCollection("MOE_CALL")
db.MOE_CALL.createIndex({"MSISDN":1})
db.createCollection("MO_CALL")
db.MO_CALL.createIndex({"MSISDN":1})
db.createCollection("MO_SMS")
db.MO_SMS.createIndex({"MSISDN":1})
db.createCollection("MT_CALL")
db.MT_CALL.createIndex({"MSISDN":1})
db.createCollection("MT_SMS")
db.MT_SMS.createIndex({"MSISDN":1})
use GEO
db.dropDatabase()
use GEO
db.createCollection("MSISDN")
db.MSISDN.createIndex({"MSISDN":1},{"unique":1})
db.MSISDN.createIndex({"LOCATION":"2dsphere"})
use HOURLY_MSISDN
db.dropDatabase()
use HOURLY_MSISDN
db.createCollection("M00")
db.createCollection("M01")
db.createCollection("M02")
db.createCollection("M03")
db.createCollection("M04")
db.createCollection("M05")
db.createCollection("M06")
db.createCollection("M07")
db.createCollection("M08")
db.createCollection("M09")
db.createCollection("M10")
db.createCollection("M11")
db.createCollection("M12")
db.createCollection("M13")
db.createCollection("M14")
db.createCollection("M15")
db.createCollection("M16")
db.createCollection("M17")
db.createCollection("M18")
db.createCollection("M19")
db.createCollection("M20")
db.createCollection("M21")
db.createCollection("M22")
db.createCollection("M23")
db.M00.createIndex({"MSISDN":1},{"unique":1})
db.M01.createIndex({"MSISDN":1},{"unique":1})
db.M02.createIndex({"MSISDN":1},{"unique":1})
db.M03.createIndex({"MSISDN":1},{"unique":1})
db.M04.createIndex({"MSISDN":1},{"unique":1})
db.M05.createIndex({"MSISDN":1},{"unique":1})
db.M06.createIndex({"MSISDN":1},{"unique":1})
db.M07.createIndex({"MSISDN":1},{"unique":1})
db.M08.createIndex({"MSISDN":1},{"unique":1})
db.M09.createIndex({"MSISDN":1},{"unique":1})
db.M10.createIndex({"MSISDN":1},{"unique":1})
db.M11.createIndex({"MSISDN":1},{"unique":1})
db.M12.createIndex({"MSISDN":1},{"unique":1})
db.M13.createIndex({"MSISDN":1},{"unique":1})
db.M14.createIndex({"MSISDN":1},{"unique":1})
db.M15.createIndex({"MSISDN":1},{"unique":1})
db.M16.createIndex({"MSISDN":1},{"unique":1})
db.M17.createIndex({"MSISDN":1},{"unique":1})
db.M18.createIndex({"MSISDN":1},{"unique":1})
db.M19.createIndex({"MSISDN":1},{"unique":1})
db.M20.createIndex({"MSISDN":1},{"unique":1})
db.M21.createIndex({"MSISDN":1},{"unique":1})
db.M22.createIndex({"MSISDN":1},{"unique":1})
db.M23.createIndex({"MSISDN":1},{"unique":1})
use HOURLY
db.dropDatabase()
use HOURLY
db.createCollection("FWD_CALL_00")
db.createCollection("FWD_CALL_01")
db.createCollection("FWD_CALL_02")
db.createCollection("FWD_CALL_03")
db.createCollection("FWD_CALL_04")
db.createCollection("FWD_CALL_05")
db.createCollection("FWD_CALL_06")
db.createCollection("FWD_CALL_07")
db.createCollection("FWD_CALL_08")
db.createCollection("FWD_CALL_09")
db.createCollection("FWD_CALL_10")
db.createCollection("FWD_CALL_11")
db.createCollection("FWD_CALL_12")
db.createCollection("FWD_CALL_13")
db.createCollection("FWD_CALL_14")
db.createCollection("FWD_CALL_15")
db.createCollection("FWD_CALL_16")
db.createCollection("FWD_CALL_17")
db.createCollection("FWD_CALL_18")
db.createCollection("FWD_CALL_19")
db.createCollection("FWD_CALL_20")
db.createCollection("FWD_CALL_21")
db.createCollection("FWD_CALL_22")
db.createCollection("FWD_CALL_23")
db.createCollection("MCF_CALL_00")
db.createCollection("MCF_CALL_01")
db.createCollection("MCF_CALL_02")
db.createCollection("MCF_CALL_03")
db.createCollection("MCF_CALL_04")
db.createCollection("MCF_CALL_05")
db.createCollection("MCF_CALL_06")
db.createCollection("MCF_CALL_07")
db.createCollection("MCF_CALL_08")
db.createCollection("MCF_CALL_09")
db.createCollection("MCF_CALL_10")
db.createCollection("MCF_CALL_11")
db.createCollection("MCF_CALL_12")
db.createCollection("MCF_CALL_13")
db.createCollection("MCF_CALL_14")
db.createCollection("MCF_CALL_15")
db.createCollection("MCF_CALL_16")
db.createCollection("MCF_CALL_17")
db.createCollection("MCF_CALL_18")
db.createCollection("MCF_CALL_19")
db.createCollection("MCF_CALL_20")
db.createCollection("MCF_CALL_21")
db.createCollection("MCF_CALL_22")
db.createCollection("MCF_CALL_23")
db.createCollection("MOE_CALL_00")
db.createCollection("MOE_CALL_01")
db.createCollection("MOE_CALL_02")
db.createCollection("MOE_CALL_03")
db.createCollection("MOE_CALL_04")
db.createCollection("MOE_CALL_05")
db.createCollection("MOE_CALL_06")
db.createCollection("MOE_CALL_07")
db.createCollection("MOE_CALL_08")
db.createCollection("MOE_CALL_09")
db.createCollection("MOE_CALL_10")
db.createCollection("MOE_CALL_11")
db.createCollection("MOE_CALL_12")
db.createCollection("MOE_CALL_13")
db.createCollection("MOE_CALL_14")
db.createCollection("MOE_CALL_15")
db.createCollection("MOE_CALL_16")
db.createCollection("MOE_CALL_17")
db.createCollection("MOE_CALL_18")
db.createCollection("MOE_CALL_19")
db.createCollection("MOE_CALL_20")
db.createCollection("MOE_CALL_21")
db.createCollection("MOE_CALL_22")
db.createCollection("MOE_CALL_23")
db.createCollection("MO_CALL_00")
db.createCollection("MO_CALL_01")
db.createCollection("MO_CALL_02")
db.createCollection("MO_CALL_03")
db.createCollection("MO_CALL_04")
db.createCollection("MO_CALL_05")
db.createCollection("MO_CALL_06")
db.createCollection("MO_CALL_07")
db.createCollection("MO_CALL_08")
db.createCollection("MO_CALL_09")
db.createCollection("MO_CALL_10")
db.createCollection("MO_CALL_11")
db.createCollection("MO_CALL_12")
db.createCollection("MO_CALL_13")
db.createCollection("MO_CALL_14")
db.createCollection("MO_CALL_15")
db.createCollection("MO_CALL_16")
db.createCollection("MO_CALL_17")
db.createCollection("MO_CALL_18")
db.createCollection("MO_CALL_19")
db.createCollection("MO_CALL_20")
db.createCollection("MO_CALL_21")
db.createCollection("MO_CALL_22")
db.createCollection("MO_CALL_23")
db.createCollection("MO_SMS_00")
db.createCollection("MO_SMS_01")
db.createCollection("MO_SMS_02")
db.createCollection("MO_SMS_03")
db.createCollection("MO_SMS_04")
db.createCollection("MO_SMS_05")
db.createCollection("MO_SMS_06")
db.createCollection("MO_SMS_07")
db.createCollection("MO_SMS_08")
db.createCollection("MO_SMS_09")
db.createCollection("MO_SMS_10")
db.createCollection("MO_SMS_11")
db.createCollection("MO_SMS_12")
db.createCollection("MO_SMS_13")
db.createCollection("MO_SMS_14")
db.createCollection("MO_SMS_15")
db.createCollection("MO_SMS_16")
db.createCollection("MO_SMS_17")
db.createCollection("MO_SMS_18")
db.createCollection("MO_SMS_19")
db.createCollection("MO_SMS_20")
db.createCollection("MO_SMS_21")
db.createCollection("MO_SMS_22")
db.createCollection("MO_SMS_23")
db.createCollection("MT_CALL_00")
db.createCollection("MT_CALL_01")
db.createCollection("MT_CALL_02")
db.createCollection("MT_CALL_03")
db.createCollection("MT_CALL_04")
db.createCollection("MT_CALL_05")
db.createCollection("MT_CALL_06")
db.createCollection("MT_CALL_07")
db.createCollection("MT_CALL_08")
db.createCollection("MT_CALL_09")
db.createCollection("MT_CALL_10")
db.createCollection("MT_CALL_11")
db.createCollection("MT_CALL_12")
db.createCollection("MT_CALL_13")
db.createCollection("MT_CALL_14")
db.createCollection("MT_CALL_15")
db.createCollection("MT_CALL_16")
db.createCollection("MT_CALL_17")
db.createCollection("MT_CALL_18")
db.createCollection("MT_CALL_19")
db.createCollection("MT_CALL_20")
db.createCollection("MT_CALL_21")
db.createCollection("MT_CALL_22")
db.createCollection("MT_CALL_23")
db.createCollection("MT_SMS_00")
db.createCollection("MT_SMS_01")
db.createCollection("MT_SMS_02")
db.createCollection("MT_SMS_03")
db.createCollection("MT_SMS_04")
db.createCollection("MT_SMS_05")
db.createCollection("MT_SMS_06")
db.createCollection("MT_SMS_07")
db.createCollection("MT_SMS_08")
db.createCollection("MT_SMS_09")
db.createCollection("MT_SMS_10")
db.createCollection("MT_SMS_11")
db.createCollection("MT_SMS_12")
db.createCollection("MT_SMS_13")
db.createCollection("MT_SMS_14")
db.createCollection("MT_SMS_15")
db.createCollection("MT_SMS_16")
db.createCollection("MT_SMS_17")
db.createCollection("MT_SMS_18")
db.createCollection("MT_SMS_19")
db.createCollection("MT_SMS_20")
db.createCollection("MT_SMS_21")
db.createCollection("MT_SMS_22")
db.createCollection("MT_SMS_23")
db.FWD_CALL_00.createIndex({"MSISDN":1})
db.FWD_CALL_01.createIndex({"MSISDN":1})
db.FWD_CALL_02.createIndex({"MSISDN":1})
db.FWD_CALL_03.createIndex({"MSISDN":1})
db.FWD_CALL_04.createIndex({"MSISDN":1})
db.FWD_CALL_05.createIndex({"MSISDN":1})
db.FWD_CALL_06.createIndex({"MSISDN":1})
db.FWD_CALL_07.createIndex({"MSISDN":1})
db.FWD_CALL_08.createIndex({"MSISDN":1})
db.FWD_CALL_09.createIndex({"MSISDN":1})
db.FWD_CALL_10.createIndex({"MSISDN":1})
db.FWD_CALL_11.createIndex({"MSISDN":1})
db.FWD_CALL_12.createIndex({"MSISDN":1})
db.FWD_CALL_13.createIndex({"MSISDN":1})
db.FWD_CALL_14.createIndex({"MSISDN":1})
db.FWD_CALL_15.createIndex({"MSISDN":1})
db.FWD_CALL_16.createIndex({"MSISDN":1})
db.FWD_CALL_17.createIndex({"MSISDN":1})
db.FWD_CALL_18.createIndex({"MSISDN":1})
db.FWD_CALL_19.createIndex({"MSISDN":1})
db.FWD_CALL_20.createIndex({"MSISDN":1})
db.FWD_CALL_21.createIndex({"MSISDN":1})
db.FWD_CALL_22.createIndex({"MSISDN":1})
db.FWD_CALL_23.createIndex({"MSISDN":1})
db.MCF_CALL_00.createIndex({"MSISDN":1})
db.MCF_CALL_01.createIndex({"MSISDN":1})
db.MCF_CALL_02.createIndex({"MSISDN":1})
db.MCF_CALL_03.createIndex({"MSISDN":1})
db.MCF_CALL_04.createIndex({"MSISDN":1})
db.MCF_CALL_05.createIndex({"MSISDN":1})
db.MCF_CALL_06.createIndex({"MSISDN":1})
db.MCF_CALL_07.createIndex({"MSISDN":1})
db.MCF_CALL_08.createIndex({"MSISDN":1})
db.MCF_CALL_09.createIndex({"MSISDN":1})
db.MCF_CALL_10.createIndex({"MSISDN":1})
db.MCF_CALL_11.createIndex({"MSISDN":1})
db.MCF_CALL_12.createIndex({"MSISDN":1})
db.MCF_CALL_13.createIndex({"MSISDN":1})
db.MCF_CALL_14.createIndex({"MSISDN":1})
db.MCF_CALL_15.createIndex({"MSISDN":1})
db.MCF_CALL_16.createIndex({"MSISDN":1})
db.MCF_CALL_17.createIndex({"MSISDN":1})
db.MCF_CALL_18.createIndex({"MSISDN":1})
db.MCF_CALL_19.createIndex({"MSISDN":1})
db.MCF_CALL_20.createIndex({"MSISDN":1})
db.MCF_CALL_21.createIndex({"MSISDN":1})
db.MCF_CALL_22.createIndex({"MSISDN":1})
db.MCF_CALL_23.createIndex({"MSISDN":1})
db.MOE_CALL_00.createIndex({"MSISDN":1})
db.MOE_CALL_01.createIndex({"MSISDN":1})
db.MOE_CALL_02.createIndex({"MSISDN":1})
db.MOE_CALL_03.createIndex({"MSISDN":1})
db.MOE_CALL_04.createIndex({"MSISDN":1})
db.MOE_CALL_05.createIndex({"MSISDN":1})
db.MOE_CALL_06.createIndex({"MSISDN":1})
db.MOE_CALL_07.createIndex({"MSISDN":1})
db.MOE_CALL_08.createIndex({"MSISDN":1})
db.MOE_CALL_09.createIndex({"MSISDN":1})
db.MOE_CALL_10.createIndex({"MSISDN":1})
db.MOE_CALL_11.createIndex({"MSISDN":1})
db.MOE_CALL_12.createIndex({"MSISDN":1})
db.MOE_CALL_13.createIndex({"MSISDN":1})
db.MOE_CALL_14.createIndex({"MSISDN":1})
db.MOE_CALL_15.createIndex({"MSISDN":1})
db.MOE_CALL_16.createIndex({"MSISDN":1})
db.MOE_CALL_17.createIndex({"MSISDN":1})
db.MOE_CALL_18.createIndex({"MSISDN":1})
db.MOE_CALL_19.createIndex({"MSISDN":1})
db.MOE_CALL_20.createIndex({"MSISDN":1})
db.MOE_CALL_21.createIndex({"MSISDN":1})
db.MOE_CALL_22.createIndex({"MSISDN":1})
db.MOE_CALL_23.createIndex({"MSISDN":1})
db.MO_CALL_00.createIndex({"MSISDN":1})
db.MO_CALL_01.createIndex({"MSISDN":1})
db.MO_CALL_02.createIndex({"MSISDN":1})
db.MO_CALL_03.createIndex({"MSISDN":1})
db.MO_CALL_04.createIndex({"MSISDN":1})
db.MO_CALL_05.createIndex({"MSISDN":1})
db.MO_CALL_06.createIndex({"MSISDN":1})
db.MO_CALL_07.createIndex({"MSISDN":1})
db.MO_CALL_08.createIndex({"MSISDN":1})
db.MO_CALL_09.createIndex({"MSISDN":1})
db.MO_CALL_10.createIndex({"MSISDN":1})
db.MO_CALL_11.createIndex({"MSISDN":1})
db.MO_CALL_12.createIndex({"MSISDN":1})
db.MO_CALL_13.createIndex({"MSISDN":1})
db.MO_CALL_14.createIndex({"MSISDN":1})
db.MO_CALL_15.createIndex({"MSISDN":1})
db.MO_CALL_16.createIndex({"MSISDN":1})
db.MO_CALL_17.createIndex({"MSISDN":1})
db.MO_CALL_18.createIndex({"MSISDN":1})
db.MO_CALL_19.createIndex({"MSISDN":1})
db.MO_CALL_20.createIndex({"MSISDN":1})
db.MO_CALL_21.createIndex({"MSISDN":1})
db.MO_CALL_22.createIndex({"MSISDN":1})
db.MO_CALL_23.createIndex({"MSISDN":1})
db.MO_SMS_00.createIndex({"MSISDN":1})
db.MO_SMS_01.createIndex({"MSISDN":1})
db.MO_SMS_02.createIndex({"MSISDN":1})
db.MO_SMS_03.createIndex({"MSISDN":1})
db.MO_SMS_04.createIndex({"MSISDN":1})
db.MO_SMS_05.createIndex({"MSISDN":1})
db.MO_SMS_06.createIndex({"MSISDN":1})
db.MO_SMS_07.createIndex({"MSISDN":1})
db.MO_SMS_08.createIndex({"MSISDN":1})
db.MO_SMS_09.createIndex({"MSISDN":1})
db.MO_SMS_10.createIndex({"MSISDN":1})
db.MO_SMS_11.createIndex({"MSISDN":1})
db.MO_SMS_12.createIndex({"MSISDN":1})
db.MO_SMS_13.createIndex({"MSISDN":1})
db.MO_SMS_14.createIndex({"MSISDN":1})
db.MO_SMS_15.createIndex({"MSISDN":1})
db.MO_SMS_16.createIndex({"MSISDN":1})
db.MO_SMS_17.createIndex({"MSISDN":1})
db.MO_SMS_18.createIndex({"MSISDN":1})
db.MO_SMS_19.createIndex({"MSISDN":1})
db.MO_SMS_20.createIndex({"MSISDN":1})
db.MO_SMS_21.createIndex({"MSISDN":1})
db.MO_SMS_22.createIndex({"MSISDN":1})
db.MO_SMS_23.createIndex({"MSISDN":1})
db.MT_CALL_00.createIndex({"MSISDN":1})
db.MT_CALL_01.createIndex({"MSISDN":1})
db.MT_CALL_02.createIndex({"MSISDN":1})
db.MT_CALL_03.createIndex({"MSISDN":1})
db.MT_CALL_04.createIndex({"MSISDN":1})
db.MT_CALL_05.createIndex({"MSISDN":1})
db.MT_CALL_06.createIndex({"MSISDN":1})
db.MT_CALL_07.createIndex({"MSISDN":1})
db.MT_CALL_08.createIndex({"MSISDN":1})
db.MT_CALL_09.createIndex({"MSISDN":1})
db.MT_CALL_10.createIndex({"MSISDN":1})
db.MT_CALL_11.createIndex({"MSISDN":1})
db.MT_CALL_12.createIndex({"MSISDN":1})
db.MT_CALL_13.createIndex({"MSISDN":1})
db.MT_CALL_14.createIndex({"MSISDN":1})
db.MT_CALL_15.createIndex({"MSISDN":1})
db.MT_CALL_16.createIndex({"MSISDN":1})
db.MT_CALL_17.createIndex({"MSISDN":1})
db.MT_CALL_18.createIndex({"MSISDN":1})
db.MT_CALL_19.createIndex({"MSISDN":1})
db.MT_CALL_20.createIndex({"MSISDN":1})
db.MT_CALL_21.createIndex({"MSISDN":1})
db.MT_CALL_22.createIndex({"MSISDN":1})
db.MT_CALL_23.createIndex({"MSISDN":1})
db.MT_SMS_00.createIndex({"MSISDN":1})
db.MT_SMS_01.createIndex({"MSISDN":1})
db.MT_SMS_02.createIndex({"MSISDN":1})
db.MT_SMS_03.createIndex({"MSISDN":1})
db.MT_SMS_04.createIndex({"MSISDN":1})
db.MT_SMS_05.createIndex({"MSISDN":1})
db.MT_SMS_06.createIndex({"MSISDN":1})
db.MT_SMS_07.createIndex({"MSISDN":1})
db.MT_SMS_08.createIndex({"MSISDN":1})
db.MT_SMS_09.createIndex({"MSISDN":1})
db.MT_SMS_10.createIndex({"MSISDN":1})
db.MT_SMS_11.createIndex({"MSISDN":1})
db.MT_SMS_12.createIndex({"MSISDN":1})
db.MT_SMS_13.createIndex({"MSISDN":1})
db.MT_SMS_14.createIndex({"MSISDN":1})
db.MT_SMS_15.createIndex({"MSISDN":1})
db.MT_SMS_16.createIndex({"MSISDN":1})
db.MT_SMS_17.createIndex({"MSISDN":1})
db.MT_SMS_18.createIndex({"MSISDN":1})
db.MT_SMS_19.createIndex({"MSISDN":1})
db.MT_SMS_20.createIndex({"MSISDN":1})
db.MT_SMS_21.createIndex({"MSISDN":1})
db.MT_SMS_22.createIndex({"MSISDN":1})
db.MT_SMS_23.createIndex({"MSISDN":1})
db.FWD_CALL_00.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_01.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_02.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_03.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_04.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_05.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_06.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_07.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_08.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_09.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_10.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_11.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_12.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_13.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_14.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_15.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_16.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_17.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_18.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_19.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_20.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_21.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_22.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.FWD_CALL_23.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_00.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_01.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_02.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_03.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_04.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_05.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_06.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_07.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_08.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_09.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_10.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_11.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_12.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_13.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_14.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_15.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_16.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_17.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_18.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_19.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_20.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_21.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_22.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MCF_CALL_23.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_00.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_01.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_02.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_03.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_04.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_05.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_06.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_07.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_08.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_09.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_10.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_11.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_12.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_13.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_14.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_15.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_16.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_17.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_18.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_19.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_20.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_21.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_22.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MOE_CALL_23.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_00.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_01.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_02.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_03.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_04.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_05.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_06.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_07.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_08.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_09.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_10.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_11.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_12.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_13.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_14.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_15.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_16.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_17.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_18.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_19.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_20.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_21.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_22.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_CALL_23.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_00.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_01.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_02.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_03.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_04.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_05.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_06.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_07.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_08.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_09.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_10.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_11.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_12.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_13.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_14.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_15.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_16.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_17.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_18.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_19.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_20.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_21.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_22.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MO_SMS_23.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_00.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_01.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_02.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_03.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_04.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_05.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_06.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_07.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_08.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_09.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_10.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_11.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_12.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_13.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_14.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_15.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_16.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_17.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_18.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_19.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_20.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_21.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_22.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_CALL_23.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_00.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_01.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_02.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_03.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_04.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_05.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_06.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_07.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_08.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_09.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_10.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_11.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_12.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_13.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_14.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_15.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_16.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_17.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_18.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_19.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_20.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_21.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_22.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })
db.MT_SMS_23.createIndex({"DATETIME":1},{ expireAfterSeconds: 72000 })