function play(song) {
    var audio = new Audio(song);
    audio.play();
}
function pause(song) {
    //console.log("yuh");
    var audio = new Audio(song);
    audio.pause();
    audio.currentTime = 0;
}
function addSong(currentsong){
    const node = document.createElement("<h4>");
    const textnode = document.createTextNode("Current song: " + currentsong);
    node.appendChild(textnode);
    document.getElementById("current").appendChild(node);
}
function removeSong(){
    const list = document.getElementById("current");
    list.removeChild(list.firstElementChild);
}
var allsongs = {'all_i_want.mp3': "All I Wany by Kodaline", 'put_on_a_smile.mp3':"Put on a Smile by Silk Sonic", 'i_hate_u.mp3': "I Hate U by SZA", 'love_on_top.mp3': "Love on Top by Beyonce", 'levitating.mp3': "Levitating by Dua Lipa", 'seven.mp3': "777 by Silk Sonic", '3_nights.mp3': "3 Nights by Dominic Fike", 'consideration.mp3': "Consideration by Rihanna", 'telepatia.mp3': "Telepatia by Kali Uchis"};
var sadsongs = ['all_i_want.mp3', 'put_on_a_smile.mp3', 'i_hate_u.mp3'];
var chillsongs = ['3_nights.mp3','consideration.mp3','telepatia.mp3'];
var happysongs = ['levitating.mp3','love_on_top.mp3','seven.mp3'];
//when the user clicks anywhere on the page
document.addEventListener('click', async () => {
  // Prompt user to select any serial port.
  var port = await navigator.serial.requestPort();
  // be sure to set the baudRate to match the ESP32 code
  await port.open({ baudRate: 115200 });

  let decoder = new TextDecoderStream();
  inputDone = port.readable.pipeTo(decoder.writable);
  inputStream = decoder.readable;

  reader = inputStream.getReader();
  readLoop();

});


async function readLoop() {
  twistthru = 0;  
  firstsong = 0;
  secondsong = 0;
  thirdsong = 0;
  genre = "";  
  sadsongcount = 0; 
  chillsongcount = 0; 
  happysongcount = 0;  
  playing = "";
  count = 0;  
  counterVal = 0;
  skip = 0;
  lastplay = 0;
  while (true) {
    const { value, done } = await reader.read();
    if (done) {
      // Allow the serial port to be closed later.
      console.log("closing connection")
      reader.releaseLock();
      break;
    }
    if (value) {
        try {
            
            let jsonval = JSON.parse(value); // <-- no errors
            console.log(jsonval);
            if (jsonval["b"] == 0 && count == 0){
                count +=1;
                if (skip == 0){
                    
                    document.getElementById("songinfo").innerHTML= "";
                    genre = "sad"
                    if (lastplay){
                        playing.pause();
                        lastplay = 0;
                    }
                    document.body.style.backgroundImage = "url('rain.gif')";
                    skip +=1;
                    playing = new Audio(sadsongs[sadsongcount]);
                    document.getElementById("current").innerHTML= "Current song: " + allsongs[sadsongs[sadsongcount]];
                    playing.play();
                    sadsongcount = (sadsongcount + 1) %  sadsongs.length;
                    
                    
                }
                else if (skip == 1){ 
                    document.getElementById("songinfo").innerHTML= "";
                    genre = "chill"
                    playing.pause();
                    playing.currentTime= 0;
                    document.body.style.backgroundImage = "url('chill.gif')";          
                    skip +=1;
                    playing = new Audio(chillsongs[chillsongcount]);
                    document.getElementById("current").innerHTML= "Current song: " + allsongs[chillsongs[chillsongcount]];
                    playing.play();
                    chillsongcount = (chillsongcount + 1) %  chillsongs.length;
                    
                }
                else if (skip == 2){
                    document.getElementById("songinfo").innerHTML= "";
                    genre = "happy";
                    playing.pause();
                    document.body.style.backgroundImage = "url('shiny.gif')";
                    skip = 0;
                    playing = new Audio(happysongs[happysongcount]);
                    document.getElementById("current").innerHTML= "Current song: " + allsongs[happysongs[happysongcount]];
                    playing.play();
                    happysongcount = (happysongcount + 1) %  chillsongs.length;
                    lastplay +=1;
                }
            }
            if (jsonval["b"] == 1){
                count = 0; 
            }
            if (jsonval["j"] > 2000 && genre == "sad"){
                playing.pause();
                playing.currentTime= 0;
                playing = new Audio(sadsongs[sadsongcount]);
                document.getElementById("current").innerHTML= "Current song: " + allsongs[sadsongs[sadsongcount]];
                playing.play();
                sadsongcount = (sadsongcount + 1) %  sadsongs.length;
            }
            if (jsonval["j"] < 1000 && genre == "sad"){
                playing.pause();
                playing.currentTime= 0;
                playing = new Audio(sadsongs[sadsongcount]);
                document.getElementById("current").innerHTML= "Current song: " + allsongs[sadsongs[sadsongcount]];
                playing.play();
                sadsongcount = (sadsongcount + 1) %  sadsongs.length;
            }
            

            if (jsonval["p"] == 0 &&  genre == "sad" && twistthru == 0){
                document.getElementById("songinfo").innerHTML= "";
                console.log("in twist");
                twistthru +=1;
                firstsong = 0;
                secondsong = 0;
                thirdsong = 0;

            }
            if (jsonval["p"] <= 1365 && jsonval["p"] > 0 && genre == "sad" && firstsong == 0){
                document.getElementById("songinfo").innerHTML = allsongs[sadsongs[0]];
    
                firstsong += 1;
                twistthru = 0;
                secondsong = 0;
                thirdsong = 0;
            }
            if (jsonval["p"] > 1365 && jsonval["p"] <= 2730 && genre == "sad" && secondsong == 0){
                document.getElementById("songinfo").innerHTML = allsongs[sadsongs[1]];

                secondsong +=1;
                twistthru = 0;
                firstsong = 0;
                thirdsong = 0;
            }
            if (jsonval["p"] > 2730 && genre == "sad" && thirdsong == 0){
                document.getElementById("songinfo").innerHTML = allsongs[sadsongs[2]];
                thirdsong += 1;
                firstsong = 0;
                secondsong = 0;
                twistthru = 0;
            }

            //second page
            if (jsonval["j"] > 2000 && genre == "chill"){
                playing.pause();
                playing.currentTime= 0;
                playing = new Audio(chillsongs[chillsongcount]);
                document.getElementById("current").innerHTML= "Current song: " + allsongs[chillsongs[chillsongcount]];
                playing.play();
                chillsongcount = (chillsongcount + 1) %  chillsongs.length;
            }
            if (jsonval["j"] < 1000 && genre == "chill"){
                playing.pause();
                playing.currentTime= 0;
                playing = new Audio(chillsongs[chillsongcount]);
                document.getElementById("current").innerHTML= "Current song: " + allsongs[chillsongs[chillsongcount]];
                playing.play();
                chillsongcount = (chillsongcount + 1) %  chillsongs.length;
            }
            if (jsonval["p"] == 0 &&  genre == "chill" && twistthru == 0){
                document.getElementById("songinfo").innerHTML= "";
                console.log("in twist");
                twistthru +=1;
                firstsong = 0;
                secondsong = 0;
                thirdsong = 0;

            }
            if (jsonval["p"] <= 1365 && jsonval["p"] > 0 && genre == "chill" && firstsong == 0){
                document.getElementById("songinfo").innerHTML = allsongs[chillsongs[0]];
                console.log("in first");
                firstsong += 1;
                twistthru = 0;
                secondsong = 0;
                thirdsong = 0;
            }
            if (jsonval["p"] > 1365 && jsonval["p"] <= 2730 && genre == "chill" && secondsong == 0){
                document.getElementById("songinfo").innerHTML = allsongs[chillsongs[1]];
                console.log("in second");
                secondsong +=1;
                twistthru = 0;
                firstsong = 0;
                thirdsong = 0;
            }
            if (jsonval["p"] > 2730 && genre == "chill" && thirdsong == 0){
                document.getElementById("songinfo").innerHTML = allsongs[chillsongs[2]];
                thirdsong += 1;
                firstsong = 0;
                secondsong = 0;
                twistthru = 0;
            }

            //third page
            if (jsonval["j"] > 2000 && genre == "happy"){
                playing.pause();
                playing.currentTime= 0;
                playing = new Audio(happysongs[happysongcount]);
                document.getElementById("current").innerHTML= "Current song: " + allsongs[happysongs[happysongcount]];
                playing.play();
                happysongcount = (happysongcount + 1) %  happysongs.length;
            }
            if (jsonval["j"] < 1000 && genre == "happy"){
                playing.pause();
                playing.currentTime= 0;
                playing = new Audio(happysongs[happysongcount]);
                document.getElementById("current").innerHTML= "Current song: " + allsongs[happysongs[happysongcount]];
                playing.play();
                happysongcount = (happysongcount + 1) %  happysongs.length;
            }
            if (jsonval["p"] == 0 &&  genre == "happy" && twistthru == 0){
                document.getElementById("songinfo").innerHTML= "";
                console.log("in twist");
                twistthru +=1;
                firstsong = 0;
                secondsong = 0;
                thirdsong = 0;

            }
            if (jsonval["p"] <= 1365 && jsonval["p"] > 0 && genre == "happy" && firstsong == 0){
                document.getElementById("songinfo").innerHTML = allsongs[happysongs[0]];
                console.log("in first");
                firstsong += 1;
                twistthru = 0;
                secondsong = 0;
                thirdsong = 0;
            }
            if (jsonval["p"] > 1365 && jsonval["p"] <= 2730 && genre == "happy" && secondsong == 0){
                document.getElementById("songinfo").innerHTML = allsongs[happysongs[1]];
                console.log("in second");
                secondsong +=1;
                twistthru = 0;
                firstsong = 0;
                thirdsong = 0;
            }
            if (jsonval["p"] > 2730 && genre == "happy" && thirdsong == 0){
                document.getElementById("songinfo").innerHTML = allsongs[happysongs[2]];
                thirdsong += 1;
                firstsong = 0;
                secondsong = 0;
                twistthru = 0;
            }
          
          } catch (err) {
            continue;
          }


    }
  }
};

