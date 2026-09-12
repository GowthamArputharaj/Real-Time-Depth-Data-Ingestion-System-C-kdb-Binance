/ common/schema.q

depthSchema:([] time:`timestamp$(); sym:`symbol$(); received_at:`timestamp$(); side:`symbol$(); price:`float$(); size:`float$());

depthCols:`time`sym`received_at`side`price`size;

