const ffi = require('ffi-napi');

path = ''
if (process.platform === 'win32') {
    path = '../../ATC/build/ATC.dll'
} else {
    path = '../../ATC/build/ATC.so'
}

const ATC = ffi.Library(path, { //Change path after the working path of the file you include this from
    'thisReturnsOne': ['int', []]
});

module.exports = { ATC };