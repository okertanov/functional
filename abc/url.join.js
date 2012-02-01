// Simplified
TK2.getImageHTML = function(size, zoom, sensor, markers) {
    var url = [ 'http://maps.google.com/maps/api/staticmap',
        '?center=', markers[0].latitude, ',', markers[0].longitude,
        '&size=', size,
        '&zoom=', zoom,
        '&sensor=', sensor ];
    for (var i = 0; i < markers.length; i++) {
        url.push(markers[i].addMarker());
    }
    return '<img src="' + url.join('') + '" alt="The map" />';
}
