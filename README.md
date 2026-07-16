# FreeWare
**FreeWare** is an upcoming **tower defence** game where you protect your computer from incoming malware!

Inspired by *[Plants vs. Zombies](https://plantsvszombies.wiki.gg/wiki/Plants_vs._Zombies)*, you free RAM that has been taken over by malware to deploy and run software on your desktop that defends your firewall from oncoming threats in row-based combat. Although the firewall can defend itself to an extent, once it has been breached, it's game over, and your computer becomes victim to the viruses!

**Table of Contents**
- [Premise](#premise)
- [Gameplay Overview](#gameplay-overview)
	- [Apps](#apps)
	- [Desktops](#desktops)
- [Development](#development)

## Premise
You are a homeless, jobless Computer Science graduate in the year 203X! AI has made it much more difficult to get hired as a software developer than the decades prior, although given you are too focused on developing revolutionary free-and-open-source software (FOSS), you wouldn't fare very well under a corporate job anyway. Fortunately, you've invested heavily into your collection of miscellaneous laptops that allow you to develop and test your software.

However, despite your programming genius, you never quite excelled in Cybersecurity - a field which has only gotten more complex since the advent of AI-written malware. As a result, you've managed to consistently install malware on every device you use, hogging your machines' resources and putting your work at risk! With little else to turn to, it is up to you to defend the future of software with the way you know best: more software!

However, as you battle the unwanted guests, you begin to notice patterns. Not all of this malware is as random as you'd expect. Nay, it would appear that many are specifically targeted at you! Could it be that your work has attracted the attention of nefarious governments and organisations that seek an end to the FOSS movement that rivals their own paid, sketchy software?

With your skills and the help of the FOSS community, you must defend your computers from these attackers and free software for the future of humanity!

## Gameplay Overview
> [!NOTE]
> Although the vast majority of malware (and softare components) work silently behind the scenes of a user's computer, this game takes creative liberties to create a more visually-engaging experience.

The battlefield is your Desktop, and as you progress, this will change depending on which Operating System you are using.

As with many desktops, your Apps are bound to a grid of platform-specific dimensions, and only one app can occupy a tile at a time. Malware, however, are more free to move, typically (but not always) targeting a row as they head towards your Firewall that lies on the left of your Desktop.

Different Malware will have different characteristics and abilities, but generally-speaking, they will appear from the right side of your Desktop and, attracted to your Firewall, head towards it while attacking your Apps that may stand in their way.

Your Firewall is capable of defending itself to an extent, but these defences are overwhelmed, it will shatter, leaving your entire system exposed - game over. However, if you successfully defend the onslaught of Malware, you advance to the next level!

Between levels, you will gain access to new software and upgrades that will give you an edge over your attackers and open up new ways to formulate defences.

Furthermore, as you make progress on your own software projects, you will need to migrate between computers and Operating Systems, presenting new challenges yet also opportunities.

### Apps
Apps can typically be placed on your Desktop grid and occupy a single cell. Once running, they will perform whatever tasks they are programmed to do. Many Apps are built to attack oncoming malware, but others are focused on more specialised tasks.

However, Apps require RAM to run on your machine - RAM which is being stolen by Malware. Your Firewall will periodically free some RAM, but you will ultimately want to increase your available RAM more quickly in order to run more powerful Apps.

Some "classes" of Apps include:
- **Attackers** -> Attack oncoming Malware directly.
- **Uncrackables** -> Stall Malware through sheer durability.
- **Antiviruses** -> Free up RAM by tackling Malware running in the background.
- **Compatibility Layers / Virtual Machines / Emulators** -> Allow you to run software intended for other platforms.
- **Utilities** -> Assist other Apps in specialised ways.

### Desktops
As you progress, you will switch between operating systems, each with their own Desktops, dedicatd Malware, dedicated Apps, and gimmicks:

These include:
- Macroslop Windoors XD / 10 / 13
- Lemon vernOS
- Freax Kimuntu / Ushanka / Prime / Ace / Egg!_OS
- SilverOS
- FreeLSD / OpenLSD / WebLSD / PhantomLSD
- ThirdOS

## Development
FreeWare is currently being developed in modern C++ (i.e., C++26 at this time) with the help of [SDL3](https://wiki.libsdl.org/SDL3/FrontPage), independently by [Kojo Bailey](https://github.com/KojoBailey). As such, development will be slow and sure to meet many setbacks, but it is a game of the likes which I have been planning for years as a long-time fan of *Plants vs. Zombies*.

There is no roadmap set out yet considering I could very well end up rewriting the entire game in a different programming language at this stage, but I do hope to have little fun playtests up and running before too long.

As this is a learning experience as well as a passion project, contributions are closed for the timebeing, although I am always open to feedback. Likewise, AI has not and will not be used to generate code.

As of now, FreeWare is licensed under the **GNU Affero General Public License v3.0**. This essentially means that the code for this project cannot be forked or re-distributed without also being kept as open-source under this same license. Since this is a game, this license is subject to change, but keeping it open-source is a goal all the same. It is only fitting given the game's theme, after all.