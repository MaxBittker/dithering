// Our Twitter library
var Twit = require('twit');

// We need to include our configuration file
var T = new Twit(require('./config.js'));
var request = require('request');
var open = require("open");
var fs = require("fs");
var gm = require("gm").subClass({
    imageMagick: true
});
var spark = require("spark");
count = 0;
c2 = 0;

function watchTag() {

    var stream = T.stream('statuses/filter', {
        track: ['art']
    })

    stream.on('tweet', function(tweet) {
        try {
            var imgurl = tweet.entities.media[0].media_url
                // console.log(imgurl)
            var id = imgurl.split("/")[4]
                // console.log(id)

            var stream = request(imgurl).pipe(fs.createWriteStream('img/' + count + ".jpg"))
            count++;
            stream.on('finish', function() {

                    gm("img/" + c2 + ".jpg").sharpen(3).resize(384).monochrome().normalize().gamma(2.3).orderedDither("All",7).write('output/' + count + ".bmp", function(err) {
                        if (!err) console.log('wrote: ' + id);
                    });
                    c2++
                })
                // open(imgurl);
        } catch (e) {
            // console.log(e)
        }
    })


}

watchTag();
