var fs = require('fs');
var express = require('express');
var https = require('https');
var http = require('http');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const basicAuth = require('express-basic-auth');

//const pKey = fs.readFileSync('./certs/ca.key');
//const cert = fs.readFileSync('./certs/ca.crt');

//const cred ={key: pKey, cert: cert};

const accountRouter = require('./routes/account');
const cardRouter = require('./routes/card');
const loginRouter = require('./routes/login');
const actionsRouter = require('./routes/actions');
const cryptoaccountRouter = require('./routes/cryptoaccount');
const ratesRouter = require('./routes/rates');
const cryptoactionRouter = require('./routes/cryptoaction');

var app = express();
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(basicAuth({users: {'admin': '1234'}}))

app.use('/login', loginRouter);
app.use('/account', accountRouter);
app.use('/card', cardRouter);
app.use('/actions', actionsRouter);
app.use('/cryptoaccount', cryptoaccountRouter);
app.use('/rates', ratesRouter);
app.use('/cryptoaction', cryptoactionRouter);


//const httpsServer = https.createServer(cred, app);
const httpServer = http.createServer(app);
httpServer.listen(3000);

//httpServer.listen(3000);


module.exports = app;
