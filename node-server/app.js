var osc = require('node-osc');
var util = require('util');
var express = require('express');

// set io webserver
var app = require('express.io')()
app.http().io()

// set OSC server
var oscServer = new osc.Server(8080, 'localhost');

// console.log(app);
app.use(express.static(__dirname + '/public'));

// ready 
app.io.route('ready', function(req) {
    // console.log("socket.io ready");
    oscServer.on("message", function (msg, rinfo) {
            // console.log(msg);

            var sushi_id = msg[2][1];
            // console.log('sushi_id', sushi_id);

            req.io.emit('sushi', {
                "sushi" : sushi_id
            })
    })

});

app.get('/', function(req, res) {
    res.sendfile(__dirname + '/pages/index.html')
})

// app.get('/js/jquery.js', function(req, res) {
//     res.sendfile(__dirname + '/public/jquery.js')
// })

// app.get('/img/:imageName', function(req, res) {
//     var img_path = __dirname + '/public/images/'+req.params.imageName;
//     //console.log(img); //path
//     var img = fs.readFileSync(img_path);
//     res.writeHead(200, {'Content-Type': 'image/png' });
//     res.end(img, 'binary');
//     // res.sendfile(img)
// })



app.listen(8080)
