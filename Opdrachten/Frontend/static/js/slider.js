import React from 'react';
import ReactDOM from 'react-dom';
import 'react-slideshow-image/dist/styles.css';
import { Fade } from 'react-slideshow-image';

const images = [
    '../static/media/kasProject1.JPG',
    '../static/media/kasProject2.JPG',
    '../static/media/kasProject3.JPG'
];

const divStyle = {
    width: '100%',
    height: '100%',
    backgroundSize: 'cover',
    backgroundPosition: 'center',
    backgroundRepeat: 'no-repeat'
};

function ImageSlider() {
    return (
        <div className="slide-container">
            <Fade>
                {images.map((image, index) => (
                    <div key={index}>
                        <div
                            style={{
                                ...divStyle,
                                backgroundImage: `url(${image})`
                            }}
                        ></div>
                    </div>
                ))}
            </Fade>
        </div>
    );
}

// Render the ImageSlider component into the div with id="slider-root"
ReactDOM.render(<ImageSlider />, document.getElementById('slider-root'));
