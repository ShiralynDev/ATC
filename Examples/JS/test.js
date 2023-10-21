// Note that I, Sparkles am not a JS dev so please help me expand and improve this code

const Module = require('../../ATC/JSWrapper/ATC.js');

Module.onRuntimeInitialized = function () {
    if (Module._thisReturnsOne()) {
        console.log("this works")
        return 1;
    }
};