\p 5011

\l common/schema.q
depth:depthSchema;

.u.upd:{[tbl;row] tbl insert row;}

tp_handle:hopen `::5010

/ 3. Every 30 seconds, flush memory to the temporary disk partition
flush_to_disk:{[]
    if[0=count depth; -1 (string .z.T)," - No data arrived. Flush skipped."; :()];  / Skip if no new data arrived
    
    / Define the intraday disk path for today's date
    intra_dir:hsym `$"intraday/",(string .z.D),"/depth/";
    
    / Enumerate symbols against the global sym file and APPEND (upsert) to disk
    / intra_dir upsert .Q.en[`:hdb] depth;
    intra_root:hsym `$"intraday";
    intra_dir upsert .Q.en[intra_root] depth;
    
    rowCount: count depth;
    
    / CRITICAL: Clear memory instantly to free up RAM
    delete from `depth;
    
    -1 (string .z.T)," - Flushed ",(string rowCount)," ticks to disk. Memory cleared.";
    }

/ 4. Set kdb+ system timer to run every 05 seconds (05000 milliseconds)
\t 5000
.z.ts:{flush_to_disk[]}

/ 5. Midnight Rollover: Move the fully compiled intraday data to the official HDB
.u.endofday:{[]
    -1 "=== Processing Midnight Rollover ===";
    
    / FIX: Use system string format to turn off the timer inside the function
    system "t 0"; 
    
    flush_to_disk[]; / Final flush of any remaining ticks
    
    intra_dir:hsym `$"intraday/",(string .z.D),"/depth/";
    hdb_dir:hsym `$"hdb/",(string .z.D),"/depth/";
    
    / Read the full day's data from the temporary disk directory
    day_data: get intra_dir;
    / day_data: select from intra_dir;
    
    / Sort by sym on disk (Strict requirement for the parted attribute)
    `sym xasc `day_data;
    
    / Save cleanly to the official structured HDB path
    hdb_dir set day_data;
    
    / Apply the parted attribute (#p) so traders can query 1000 syms easily
    @[hdb_dir; `sym; p#];
    
    / Clean up temporary intraday files from disk
    hcode: "rm -rf intraday/",(string .z.D);
    system hcode;
    
    / FIX: Use system string format to restart the 30-second timer
    system "t 30000";
    }


