/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 */

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 100;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// **** array to keep track for empty seats
var emptyseats = [];

// **** track of passanger house
var passengerhouse = [];

// **** track of passanger house
var DROPPOINTS = 0;

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });

    // load application
    load();
});

// unload application
$(window).unload(function() {
    unload();
});

/**
 * Renders seating chart.
 */
function chart()
{
    var html = "<ol start='0'>";
    for (var i = 0; i < shuttle.seats.length; i++)
    {
        if (shuttle.seats[i] == null)
        {
            html += "<li>Empty Seat</li>";
        }
        else
        {
            //alert(shuttle.seats[SEATS]); 
            //shuttle.seats.push[P.placemark.getName()];
            //console.log(shuttle.seats[currseat]);
            html += "<li>" + shuttle.seats[i] + "</li>";
        }
    }
    html += "</ol>";
    $("#chart").html(html);
}

/**
 * ***********************************  Default Announcement *************************
 */
function defaultAnnouncement(){
    window.setTimeout(function() {
        announce("no announcements at this time");
    }, 5000);
}       
         

/**
 * ***********************************  Announcement *************************
 */
function announce(str)
{
    $("#announcements").html(str);
    defaultAnnouncement();
}


/**
 * ***********************************   Drop points *************************
 */
function droppoints(){
    DROPPOINTS++;
}

/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

// ************************* emptyseat & passanger house*********************************
function emptySeats() 
{
    for (var i = SEATS-1 ;i >= 0; i--)
    {
        emptyseats.push(i); 
        //passengerhouse   
    }
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();
    
    //empty seats
    emptySeats();

    // populate Earth with passengers and houses
    populate();
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;    
        return false;
    }
  
    return true;
}

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}




/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker(
            {
                icon: "https://google-maps-icons.googlecode.com/files/home.png",
                map: map,
                position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
                title: house
            }
        );
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);

        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        });

        // TODO: remember passenger's placemark and marker for pick-up's sake
        PASSENGERS[i].placemark = placemark;
        PASSENGERS[i].marker = marker;
        //console.log(PASSENGERS[i].placemark +" "+i );
    }
}

/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}


/**
 * Picks up nearby passengers.
 */
 
function pickup()
{
    //control variable for announcement
    var check = 0;
    
    // i) where to know the passanger are? //PASSENGERS.length
    for (var i = 0; i < PASSENGERS.length; i++)                         //executes loop for say,106 times for all passenger 
    {     
        var lat = PASSENGERS[i].placemark.getGeometry().getLatitude();  // get lat of a passenger    
        var lng = PASSENGERS[i].placemark.getGeometry().getLongitude(); // get lng of a passenger
        
        //1. detect passange on range
        var dis = shuttle.distance(lat, lng);               //calculates distance from shuttel to passengers 
        
        if(dis < 100) //&& emptyseats.length <= SEATS ){
        {   
             for(house in HOUSES)
             {  
                
                if(house == PASSENGERS[i].house)
                {
                    //console.log(house + " " +  PASSENGERS[i].house);                 
                    
                    var currseat = emptyseats.pop(); //use try and catch
                    //console.log("Empty seats "+ emptyseats.length);
                    if(currseat <= SEATS || currseat > 0 )
                    {
                        //2. add passangers to shuttel 
                        shuttle.seats[currseat] = PASSENGERS[i].placemark.getName();
                        //console.log("Passanger house " + PASSENGERS[i].house);
                        
                        //3. remove placemark
                        var features = earth.getFeatures();
                        features.removeChild(PASSENGERS[i].placemark);
                        
                        //4. remove marker //PASSENGERS[i].marker
                        PASSENGERS[i].marker.setMap(null);
                        
                        //5. display passanger in shuttel
                        chart();
                        
                        //Remove sordinates of the passenger
                        var point = earth.createPoint("");
                        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
                        point.setLatitude(0.0);
                        point.setLongitude(0.0);
                        point.setAltitude(0.0);
                        
                        PASSENGERS[i].placemark.setGeometry(point);
                        
                        //$("#announcements").html(shuttle.seats[currseat]);
                        //defaultAnnouncement();
                        check =9;
                        announce(shuttle.seats[currseat]);
                        console.log(shuttle.seats[currseat]);
                    }
                    else
                    {
                        check = -1;
                    } //if else seats available
                    
                }//end of if else house found   
                 
            } //end of for houses
            
        } // if dis
        
    } //for
    chart();
    
    // announcements
    
    if(check == -1)
    {
        //$("#announcements").html("No seats are left now");
        announce("No seats are left now");
    } 
    else 
    {   if(check == 0) {
            //$("#announcements").html("No one in range to pick");
            announce("No one in range to pick");
        } 
    }
    // clear announcement when shuttle moves // no announcements at this time
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    //alert(shuttle.seats.length);
    //var currseat = emptyseats.pop()
    
    for(passenger in shuttle.seats)
    {
        //var currseat = emptyseats.pop(); //use try and catch
        //console.log(emptyseats[i]);
        if(shuttle.seats[passenger] != null) 
        {
            //console.log(shuttle.seats[passenger]);
            for(house in HOUSES)
            {
                // house cordinates
                lat = HOUSES[house].lat;
                lng = HOUSES[house].lng;
                
                //distance from shuttle
                var dis = shuttle.distance(lat, lng);
                
                //extract house from the "name to passanger" string
                var searched = shuttle.seats[passenger].search("to ") + 3;
                var passhouse = shuttle.seats[passenger].substr(searched);
                var cmp = passhouse.localeCompare(house);
                
                //console.log(passhouse +" ... "+shuttle.seats[passenger]+" .. " +house +" ... "+cmp);
                
                if (dis < 50 && cmp == 0)
                {
                    // push seat no in empty seat array
                    //console.log(passhouse +" ... "+shuttle.seats[passenger]+" .. " +house +" ... "+cmp);
                    emptyseats.push(passenger);                  
                    
                    //$("#announcements").html(shuttle.seats[passenger]);
                    announce(shuttle.seats[passenger]);                   
                    shuttle.seats[passenger] = null;
                    droppoints();                  
                    
                    //$("#announcements").html("driver earns "+DROPPOINTS+" point(s)");
                    announce("driver earns "+DROPPOINTS+" point(s)");                 
                    break;
                }
                
            }
        }
    }
    //display passanger in shuttel
    chart();
    
    
}
