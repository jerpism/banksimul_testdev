var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const basicAuth = require('express-basic-auth');

const accountRouter = require('./routes/account');
const cardRouter = require('./routes/card');
const loginRouter = require('./routes/login');
const actionsRouter = require('./routes/actions');

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

module.exports = app;

