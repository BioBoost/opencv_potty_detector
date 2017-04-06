var player = require('play-sound')(opts = {})

const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://mqtt.labict.be')

var garageState = ''
var connected = false

client.on('connect', () => {
  client.subscribe('pottydetector/lost')
})

client.on('message', (topic, message) => {
  switch (topic) {
    case 'pottydetector/lost':
      return handleTimer(message)
  }
  console.log('No handler for topic %s', topic)
})

function handleTimer (message) {
  console.log('timer: %s', message)

  player.play('yeehaw.mp3', function(err){
    if (err) throw err
  })
}
