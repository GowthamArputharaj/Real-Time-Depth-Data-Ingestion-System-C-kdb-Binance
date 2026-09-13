/ replay.q
/ Usage: q replay.q -logFile log/tplog_2026.09.13

/ 1. Parse command line arguments
args:.Q.def[enlist[`logFile]!enlist "log/tplog_2026.09.13"] .Q.opt .z.x;
logFile:hsym `$args`logFile;

/ 2. Define the exact physical schema layout matching the payload
\l common/schema.q
depth:depthSchema;

/ 3. Use a flexible insert that forces list assignment 
.u.upd:{[tbl;payload] 
    tbl insert payload;
 };

/ 4. Direct Replay Execution (No complex trap function to obscure errors)
-11!logFile;

/ 5. Print status
-1 "Successfully replayed records.";
-1 "Total: ", string count depth;
show 3#depth;

