#
# /Applications/OpenOffice.org.app/Contents/MacOS/soffice "-accept=socket,host=localhost,port=2002;urp;"
#
import socket  # only needed on win32-OOo3.0.0
import uno
import unohelper
from com.sun.star.text.ControlCharacter import PARAGRAPH_BREAK
from com.sun.star.text.TextContentAnchorType import AS_CHARACTER
from com.sun.star.awt import Size

# get the uno component context from the PyUNO runtime
localContext = uno.getComponentContext()

# create the UnoUrlResolver
resolver = localContext.ServiceManager.createInstanceWithContext(
            "com.sun.star.bridge.UnoUrlResolver", localContext )

# connect to the running office
ctx = resolver.resolve( "uno:socket,host=localhost,port=2002;urp;StarOffice.ComponentContext" )
smgr = ctx.ServiceManager

# get the central desktop object
desktop = smgr.createInstanceWithContext( "com.sun.star.frame.Desktop",ctx)

# access the current writer document
document = desktop.getCurrentComponent()
#document = desktop.loadComponentFromURL("private:factory/swriter", "_blank", 0, ())

# access the document's text property
text = document.Text

# create a cursor
cursor = text.createTextCursor()

# insert the text into the document
#text.insertString( cursor, ".", 0 )

def InjectBarcode(i):
    str_fmt = "0000%dLV"
    #path_fmt = "file:///Users/nata/projects/barcode-lv.git/%s.png"
    path_fmt = "file:///C:/okertanov/projects/_unsupported_/barcode-lv.git/%s.png"

    code = str_fmt % i
    path = path_fmt % code

    oBitmaps = document.createInstance( "com.sun.star.drawing.BitmapTable" )
    oBitmaps.insertByName( code, path )
    oShape = document.createInstance( "com.sun.star.text.GraphicObject" )
    oShape.GraphicURL = oBitmaps.getByName(code)
    oShape.setSize( Size(5000,2600) )
    oShape.setPropertyValue( "AnchorType" , AS_CHARACTER )
    oShape2 = document.createInstance( "com.sun.star.text.GraphicObject" )
    oShape2.GraphicURL = oBitmaps.getByName(code)
    oShape2.setSize( Size(5000,2600) )
    oShape2.setPropertyValue( "AnchorType" , AS_CHARACTER )
    oShape3 = document.createInstance( "com.sun.star.text.GraphicObject" )
    oShape3.GraphicURL = oBitmaps.getByName(code)
    oShape3.setSize( Size(5000,2600) )
    oShape3.setPropertyValue( "AnchorType" , AS_CHARACTER )
    oShape4 = document.createInstance( "com.sun.star.text.GraphicObject" )
    oShape4.GraphicURL = oBitmaps.getByName(code)
    oShape4.setSize( Size(5000,2600) )
    oShape4.setPropertyValue( "AnchorType" , AS_CHARACTER )
    text.insertTextContent(cursor, oShape, uno.Bool(1))
    text.insertTextContent(cursor, oShape2, uno.Bool(1))
    text.insertTextContent(cursor, oShape3, uno.Bool(1))
    text.insertTextContent(cursor, oShape4, uno.Bool(1))


    #range_begin = 62519
    #range_end   = 63520 + 1

range_begin = 62519
range_end   = 63619 + 1
break_at = 11230
npages = 1

for i in range(range_begin, range_end):
    InjectBarcode(i)
    print("Page: %(npages)d, item: %(i)d\n" % {'npages':npages, 'i':i})
    if i % 11 == 0:
        npages += 1
        text.insertControlCharacter( cursor, PARAGRAPH_BREAK, 0 )
        if npages == break_at:
            break;


#oShape = document.createInstance("com.sun.star.drawing.GraphicObjectShape")
#GraphicURL = "file:///okertanov/projects/_unsupported_/github/barcode-lv/000060001 LV.png"
#embedImage = document.createInstance("com.sun.star.drawing.GraphicObjectShape")
#embedImage.setPosition(oPosition)
#embedImage.setSize(oNewSize)
#embedImage.setPropertyValue('GraphicURL', GraphicURL)
#text.insertTextContent(cursor, oShape, 1)

#page = document.getDrawPage()
#page.add(embedImage)

# Do a nasty thing before exiting the python process. In case the
# last call is a oneway call (e.g. see idl-spec of insertString),
# it must be forced out of the remote-bridge caches before python
# exits the process. Otherwise, the oneway call may or may not reach
# the target object.
# I do this here by calling a cheap synchronous call (getPropertyValue).
ctx.ServiceManager

