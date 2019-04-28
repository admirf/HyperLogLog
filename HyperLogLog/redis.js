var redis = require("redis"),
    client = redis.createClient();

var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream('categories.csv'),
    crlfDelay: Infinity
});

console.log("Starting redis hll test.");

lineReader.on('line', function (line) {
    client.pfadd('csv', line);
});

lineReader.on('close', function () {
    client.pfcount('csv', function (err, reply) {
        console.log(reply);
        process.exit();
    });
});

// process.exit();