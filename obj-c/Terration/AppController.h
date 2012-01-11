//
//  AppController.h
//  Terration
//
//  Created by Nata Kertanova on 11/15/10.
//  Copyright SIA SS 2010 . All rights reserved.
//

#import "NQCWindow.h"

@interface AppController : NSObject 
{
	IBOutlet QCView* qcView;
	IBOutlet NQCWindow* window;
}

- (IBAction) changeColorToBlue:(id)sender;

- (IBAction) enterFullScreen:(id)sender;


@end
