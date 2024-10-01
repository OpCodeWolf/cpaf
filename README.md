# Cross Platform Application Framework (CPAF)

## Information

The framework will likely start with a hodge podge of interconnects across each language, I will refactor as needed to make this compile on each platform. 

**I'm primarily focused right now on getting linux X11 windowing routines created, in the hopes to create a full fledged application from scratch, using NAPI and NODE-GYP**

Most of the methods will be programmed in the platform's native languages for example Linux will be C++. OSx will likey be using XCode or C++. Windows will also be C++. Others will be decided later.

 As each language is found to have tie-ins with each platform and NodeJS, they will be stored in this repository by platform. If there is a way to use one language across all platforms, this will be the preferred choice. 
 
I would like to find a way to cross compile the API for all platforms from each platform. Eg. I want to compile once in Linux and get a working application for Linux, Mac (OSx), and Windows. Likewise, I want to compile once in Windows and get a working application for Linux, Mac (OSx), and Windows. Etc. Rinse and repeat. 
 
 If you know something, please say something. I'm more than willing to allow others to help direct me down the right path and PR's are always welcomed.

Please note this project may take some time, as I work a full time job, have a personal electronics parts business on the side, and I'm relearning windowing across multiple platforms. I am a very quick learner and will be spending any time I can on this, but I also have a life to live. Please give me plenty enough time to respond to PR's and questions.

Right now everything looks like a mess and as I figure out how to refactor each part to make it modular it will look better. I'm not really worried about this, as eventually my brain just self cleans it automatically based on experience.

## Frequently Asked Questions

```
Q: Why don't you just use a framework that already exists like Qt or <insert name here> ?

A: I don't particularly like giving away my first born to these companies that have vague licensing or volume licensing, only to find out later that you've somehow violated their precious license and you are forced to scrap everything you have been building for the past 2 years, unless you pay them an ongodly fortune. Thusly, I will be creating my own framework from scratch. Period.
```

```
Q: Why would you do this?

A: I need an application framework really soon, for projects/products I will be creating. I don't want to have to rewrite everything to please a 3rd party company or be wrapped up in their licensing schemes. Plus I like to learn new things.
```

```
Q: Can other people use this framework in their private or commercial projects?

A: Yes, absolutely! The only way to beat the competition is to squash them at their own game.
```

```
Q: Will you be using many 3rd party libraries in the creation of this?

A: Some are unavoidable, but No in general. I will be creating the code from scratch, with no influence or guidence from outside companies or organizations. If I can I will replace any 3rd party code with my own.
```

```
Q: How long have you been programming?

A: I've been in the field for over 40 years. I'm seasoned. :)
```

```
Q: You mispelled something, will you fix it?

A: You, have a way to enter text and send it to me. You, should use that gift called a brain, learn git, and submit a PR to fix it. I really don't need keyboard typo commandos telling me what I should fix, it wastes precious time. Show some initiative and support the project directly. 
```

```
Q: Will you ever make this closed source for monetary gain?

A: NO! What I build with this framework may be sold for monitary gain. These companies and organizations that make their open-source projects closed source and "ungift" their fans and customers, are all business idiots. They piss me the hell off. They need to get off the internet. I am promising that this project will never ever.. ever.. ever.. ever go closed source, unless I'm forced to for some legal reason. To which I really won't be happy about it, but it will then be temporary. If that ever happens for any reason, rest assured that I will pull out chunks of code involved in whatever legal issue and keep this project open source forever. I don't scare easily, but I tend to scare others. Yes, I have powerful Attorneys and they are very well paid.
```

```
Q: Can I help out?

A: Yes! I need all the help I can get. Submit a PR!
```

```
Q: Do you stream on twitch?

A: I have been planning on doing this for a while now. I havn't yet reoganized the time between 2 companies and personal life. In the future, this will definately be a thing. I love participating with the community and offering knowledge to others.
```

```
Q: What languages do you know?

A: I'm fluent in over 28 programming languages and currently provide my services and knowledge to Silicon Valley companies.
```

```
Q: What is your favorite language?

A: There's a few and for different reasons. Right now it's TypeScript/C++, but Python is also in close running.
```

```
Q: Did you add a license to this?

A: No, not yet. It's freeware in the meantime. I want something that's open source forever, without companies and organizations plagerizing, trademarking, and/or patenting it as their own. If you know of a good license that achieves this, please let me know.
```

## WindowAPI

This project goal will be a windowing API across multiple platforms for use with TypeScript.

### Current Exports:

- logEnvInfo()

- createWindow(null)

- setWindowTitle(string)

- setWindowSize(width: int, height: int)

- eventLoop()

### Example Typescript
```
const WindowAPI = require('../native/build/Release/windowAPI.node');

// Create the window
const window = WindowAPI.createWindow(null);

// Resize the window after it's created
window.setWindowSize(width, height);
    
// Set the windows title
window.setWindowTitle(title);

// Run the event loop to keep the window active
window.eventLoop();

```

## Test Installation
As this is a NodeJS build framework, you must install it's dependencies using the Node Package Manager like so:

```
npm i
```

## Build and Test Application

This will change in the future to support named platforms. For now you can use this in Linux/Debian

```
npm run start
```

## Particpation

If you know how to fix something without the influence of plagerizing code, please submit a PR to fix something or improve it. Please know that most developers fall under agreements or NDAs by their company or organization. Just know that what you submit will have your name attached to it.

If you submit plagerized or private work, it will be removed at the request of your company/organization and be reprogrammed in a different way, after proof has been established.

If you submit someone elses work, it will also be removed at the request of the originator after proof has been established. These are all bannable offenses.

From time to time I also like to ask AI to help solve something and for any reason it can be proved that the AI plagerized something, that code will also be removed and rewritten.

This could take a long time to complete, if everyone is plagerizing work they have submitted.

I don't give out participation trophies, but I do give credit.

If you see a credit missing, please let me know and I will fix it.

## PDP-TLC

***Please Don't Plagerize!*** 

***Think.. Learn.. Code!***



# Credits
- Node.js - Such a powerfully awesome javascript integration.
    Copyright Node.js contributors. All rights reserved. [Node.js License](https://github.com/nodejs/node/blob/main/LICENSE)
- NPM - One of the best project package managers on the planet.
    Copyright (c) npm, Inc. and Contributors
- Node-Addon-API - Node.js Addon API from the awesome Node.js folks.
    Copyright (c) 2017 [Node.js API collaborators](https://github.com/nodejs/node-addon-api#collaborators)
- TypeScript - An amazing language from Microsoft
    [Apache License - Version 2.0, January 2004](http://www.apache.org/licenses/) 

 

