var redis = require("redis"),
    client = redis.createClient();

var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream('status.csv'),
    crlfDelay: Infinity
});

console.log("Starting redis hll test.");

lineReader.on('line', function (line) {
    client.pfadd('csv', line);
});

lineReader.on('close', function () {
    client.pfcount('csv', function (err, reply) {
        console.log(reply);
        client.flushall();
        process.exit();
    });
});

// process.exit();