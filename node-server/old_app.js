var app = require('express.io')()

var osc = require('../lib/osc.js');
var util = require('util');

// Load data
var currentSardine = -1;
var sardines = [];
for (var i = 0; i < 10; i++) {
    var sardine = {};
    sardine.name = "sardine_"+i;
    sardine.x = 0;
    sardine.y = 0;
    sardines.push(sardine);
}

// server
app.http().io()

// init arduino
app.io.route('sushiId', function ( data ) {
    // body...
    console.log(data);
});

var oscServer = new osc.Server(3333, '0.0.0.0');
oscServer.on("message", function (msg, rinfo) {
    console.log("Message:");
    console.log(msg);
});

//     app.io.route('sensor', {
//         data : function (req) {
//             serialPort.on( "data", function( data ) {
//                     var json = JSON.parse( data );
//                     console.log( "data received: " + json.ping );
//                     req.io.emit('ping', {
//                              "ping" : json.ping 
//                     }) 
//             })
//         },
//         getSardine :  function (req) {
//             console.log(req.data); 
//             currentSardine = req.data.id; // store in global

//         }
//     })
// });


// Send the client html.
app.get('/', function(req, res) {
    res.sendfile(__dirname + '/pages/index.html')
})

// app.get('/', function(req, res) {
//     var home = "<a href='/rize'>Rize</a>  <a href='/sardines'>Sardine</a>";
//     res.send(home)
// })

app.get('/rize', function(req, res) {
    res.sendfile(__dirname + '/pages/index.html')
})

app.get('/sardines', function(req, res) {
    res.sendfile(__dirname + '/pages/sardine.html')
})


app.get('/jquery.js', function(req, res) {
    res.sendfile(__dirname + '/public/jquery.js')
})

app.get('/osc.js', function(req, res) {
    res.sendfile(__dirname + '/public/osc.js')
})

// API
app.get("/api/current-sardine",function(req,res){
    res.json(currentSardine);
})

app.get('/api/sardines/:id', function(req, res) {
    res.json(req.params.id)
})


app.listen(8080);
