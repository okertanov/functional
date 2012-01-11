//
//  AppController.m
//  Terration
//
//  Created by Nata Kertanova on 11/15/10.
//  Copyright SIA SS 2010 . All rights reserved.
//

#import "AppController.h"


@implementation AppController
 
- (void) awakeFromNib
{
	NSLog( @"Inside awakeFromNib" );
	
	if(![qcView loadCompositionFromFile:[[NSBundle mainBundle] 
										 pathForResource:@"earth and moon"
										 //pathForResource:@"matrix-cam" 
										 ofType:@"qtz"]]) {
		NSLog(@"Could not load composition");
	}
}

-(void)applicationDidFinishLaunching:(NSNotification *)notification
{
	NSLog( @"Inside applicationDidFinishLaunching" );
}	

- (void)windowWillClose:(NSNotification *)notification 
{
	NSLog( @"Inside windowWillClose" );
	[NSApp terminate:self];
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
	NSLog( @"Inside applicationWillTerminate" );
}

// Menu Action:
// Entering full screen mode
- (IBAction) enterFullScreen:(id)sender
{
	[window toggleFullScreen];
}

// An example of programmatically setting the value of input ports
// Notice that the QCPatchParameterView is automatically updated by setting the QCView inputs
- (IBAction) changeColorToBlue:(id)sender
{
	// Colors
	[qcView setValue:[NSColor blueColor] forInputKey:@"Top_Color"];
	[qcView setValue:[NSColor cyanColor] forInputKey:@"Middle_Color"];
	[qcView setValue:[NSColor blueColor] forInputKey:@"Bottom_Color"];
	
	// Numbers
	[qcView setValue:[NSNumber numberWithDouble:.5] forInputKey:@"Font_Size"];

	// Strings
	[qcView setValue:@"Hello World" forInputKey:@"String"];

}

@end
