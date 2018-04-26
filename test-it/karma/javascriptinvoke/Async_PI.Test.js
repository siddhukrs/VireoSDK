describe('A JavaScript function invoke', function () {
    'use strict';
    // Reference aliases
    var Vireo = window.NationalInstruments.Vireo.Vireo;
    var vireoRunner = window.testHelpers.vireoRunner;
    var fixtures = window.testHelpers.fixtures;

    var vireo;

    var jsSyncCalls = fixtures.convertToAbsoluteFromFixturesDir('javascriptinvoke/Async_PI.via');

    beforeAll(function (done) {
        fixtures.preloadAbsoluteUrls([
            jsSyncCalls
        ], done);
    });

    beforeEach(function () {
        vireo = new Vireo();

        window.PI = function () {
            return Math.PI;
        };
    });

    afterEach(function () {
        window.PI = undefined;
    });

    var sum = 0, iteration = 0;
    for(var i = 0; i < 10; i++) {
        it('with occurrence', function (done) {
            var runSlicesAsync = vireoRunner.rebootAndLoadVia(vireo, jsSyncCalls);  
            var viPathParser = vireoRunner.createVIPathParser(vireo, '%3A%3AWeb%20Server%3A%3AInteractive%3A%3AApplication%3A%3API%2Egviweb');
            runSlicesAsync(function (rawPrint, rawPrintError) {
                var duration = viPathParser('dataItem_Duration');
                sum = sum + duration;
                iteration++;
                console.log("PI - Average time: " + sum/iteration + ". Sum: " + sum);
                done();
            });
        });
    }
});
