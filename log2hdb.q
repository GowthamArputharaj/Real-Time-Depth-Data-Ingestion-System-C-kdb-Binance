/ log2hdb.q
/ Usage: q log2hdb.q -logFile log/tplog_2026.09.13 -hdbDir hdb

/ 1. Parse command line arguments
args:.Q.def[enlist[`logFile]!enlist "log/tplog_2026.09.13"] .Q.opt .z.x;
logFile:hsym `$args`logFile;
hdbDir:hsym `$"hdb";

/ 2. Canonical aggTrade schema
\l common/schema.q
depth:depthSchema;

/ 3. Batch size
\l common/config.q
batchSize:BATCH_SIZE;

/ Initialize an empty global sym file if it's a completely fresh HDB directory
if[0=count key hdbDir,`sym; (hdbDir,`sym) set `symbol$()];

/ 4. Flush batch to date-partitioned HDB
flushBatch:{[]
    if[0=count depth; :()];
    batchDate:first `date$depth`time;
    
    partitionDir:.Q.par[hdbDir;batchDate;`depth];
    batch:`time xasc depth;

    / 1. Enumerate the batch table against the HDB directory handle once
    enumBatch: .Q.en[hdbDir] batch;

    / 
    sv[`;partitionDir,`] upsert .Q.en[hdbDir] depth;

    -1 "Flushed ",string count batch," rows to ",string partitionDir;
    delete from `depth;
    :()
    };

/ 5. Handle replayed TP updates
.u.upd:{[tbl;payload]
    if[tbl<>`depth; :()];
    `depth insert payload;
    if[batchSize<=count depth; flushBatch[]];
    :()
    };

/ 6. Start replay
-1 "Starting TP log -> HDB";
-1 "Log: ",string logFile;
-1 "HDB: ",string hdbDir;
-1 "Batch size: ",string batchSize;

/ 7. Stream the TP log
-11!logFile;

/ 8. Flush remaining rows
flushBatch[];

/ 9. Finished
-1 "Replay complete";
