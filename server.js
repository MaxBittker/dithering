// Our Twitter library
var Twit = require('twit');

// We need to include our configuration file
var T = new Twit(require('./config.js'));
var open = require("open");

function watchTag() {

    var stream = T.stream('statuses/filter', {
        track: ['canada']
    })

    stream.on('tweet', function(tweet) {
        try {
            console.log(tweet.entities.media[0].media_url)
            open(tweet.entities.media[0].media_url)
        } catch (e) {}
    })


}

watchTag();
