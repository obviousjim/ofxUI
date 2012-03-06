/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFXUI_MOVING_GRAPH
#define OFXUI_MOVING_GRAPH

#include "ofxUIWidget.h"

class ofxUIMovingGraph : public ofxUIWidget
{
public:    
    ofxUIMovingGraph(float x, float y, float w, float h, vector<float> _buffer, int _bufferSize, float _min, float _max, string _name)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, _buffer, _bufferSize, _min, _max, _name);
    }
    
    ofxUIMovingGraph(float w, float h, vector<float> _buffer, int _bufferSize, float _min, float _max, string _name)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, _buffer, _bufferSize, _min, _max, _name);
    }    
    
    void init(float w, float h, vector<float> _buffer, int _bufferSize, float _min, float _max, string _name)
    {
		name = _name; 				
		kind = OFX_UI_WIDGET_MOVINGGRAPH; 
		
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect); 
		
        draw_fill = true; 
        
        buffer = _buffer;					//the widget's value
        
		bufferSize = _bufferSize; 
		max = _max; 
		min = _min; 		
		scale = rect->getHeight()*.5; 
        inc = rect->getWidth()/((float)bufferSize-1.0);         
    }
    
    void draw()
    {
        ofPushStyle(); 
        
        ofEnableBlendMode(OF_BLENDMODE_ALPHA); 
        if(draw_back)
        {
            ofFill(); 
            ofSetColor(color_back); 
            rect->draw(); 
        }
        
        if(draw_fill)
        {			
			ofNoFill(); 
			if(draw_fill_highlight)
			{
				ofSetColor(color_fill_highlight); 
			}        
			else 
			{
				ofSetColor(color_fill); 		 	
			}
            glPushMatrix();
            glTranslatef(rect->getX(), rect->getY()+scale, 0);
            ofSetLineWidth(1.5); 
            ofBeginShape();		
            for (int i = 0; i < bufferSize; i++)
            {				
                ofVertex(inc*(float)i, ofMap(buffer[i], min, max, scale, -scale, true)); 
            }
            ofEndShape();
            ofSetLineWidth(1); 
            glPopMatrix();
            
        }
		
        
        if(draw_outline)
        {
            ofNoFill();
            ofSetColor(color_outline); 
            rect->draw(); 
        }
        
        if(draw_outline_highlight)
        {
            ofNoFill();
            ofSetColor(color_outline_highlight); 
            rect->draw();          
        }
		
		if(draw_padded_rect)
		{
            ofNoFill();
            ofSetColor(color_outline_highlight); 
			paddedRect->draw(); 
		}		
        
        ofPopStyle(); 
    }
    
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
	}
	
    void addPoint(float _point)
    {
        buffer.push_back(_point); 
                
        if( buffer.size() >= bufferSize )
        {
            buffer.erase(buffer.begin(), buffer.begin()+1);
        }	        
    }
    
    vector<float> &getBuffer()
    {
        return buffer; 
    }
    
    void setBuffer(vector<float> _buffer)
    {
        buffer = _buffer; 
    }
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    vector<float> buffer;
	float max, min, scale, inc; 
	int bufferSize; 
}; 



#endif
