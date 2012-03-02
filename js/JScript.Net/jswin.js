import System;
import System.Windows.Forms;
import System.Drawing;
import Accessibility;

package Hello
{
    class HelloForm extends Form
    {
        function HelloForm()
        {
            this.Width = 640, this.Height = 480;

            Controls.Add(new RichTextBox);
            Controls[0].Text = "function Hello() \n{\n\treturn true;\n}";
            Controls[0].Left = 4, Controls[0].Top = 4;
            Controls[0].Width = this.Width - 22, Controls[0].Height = this.Height - 84;

            Controls.Add(new Button());
            Controls[1].Text = "Say";
            Controls[1].Location = new Point(24, this.Height - 72);
            Controls[1].add_Click(HelloButtonEventHandler);

            Controls.Add(new Button);
            Controls[2].Text = "Eval";
            Controls[2].Location = new Point(124, this.Height - 72);
            Controls[2].add_Click(EvalButtonEventHandler);
        }

        function HelloButtonEventHandler(sender, ev : EventArgs)
        {
            MessageBox.Show(Controls[0].Text);
        }

        function EvalButtonEventHandler(sender, ev : EventArgs)
        {
            try
            {
                eval(Controls[0].Text);
            }
            catch(e)
            {
                print(e);
            }
        }
    }
}

const main : Function = new Function("{Application.Run(new Hello.HelloForm());}");

main();

