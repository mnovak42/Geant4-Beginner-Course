'''
   M. Novak: simple custom text roles for highlighting
     - Geant4 Class Names:   :g4cname:`G4Track`
     - environment variable: :envar:`G4INSTALL`
     - files names:          :file:`fname`
'''

from docutils import nodes

def setup(app):
    ## used to reference Geant4 files from an eternal source that set here:
    app.add_role('g4file',  autolink('https://github.com/Geant4/geant4/blob/geant4-11.0-release/%s'))
    # used to reference pages from the geant4 website with main part of the link set here
    app.add_role('g4wpage', autolinkToG4Page('https://geant4.web.cern.ch/%s'))
    # as as above but to the user-doc sub-part of the page with main part of the link set here
    app.add_role('g4userdoc', autolinkToG4Page('https://geant4-userdoc.web.cern.ch/%s'))

# Use to reference Geant4 files locating at extrnal source relative to the above
# main link. Only the file name will be shown as the link text:
# :g4file:`source/particles/leptons/include/G4Electron.hh` will create a link to
# https://github.com/Geant4/geant4/blob/geant4-11.0-release/source/particles/leptons/include/G4Electron.hh
# with the link text of `G4Electron.hh`
def autolink(pattern):
    def role(name, rawtext, text, lineno, inliner, options={}, content=[]):
        url = pattern % (text,)
        # get the last element of the g4-source path that should be the file name
        g4fname = (text.split("/"))[-1]
        node = nodes.reference(rawtext, g4fname, refuri=url, **options)
        return [node], []
    return role

# Use to reference Geant4 website content given relative to the main link
# :g4wpage:`support+User Support` will create a link to
# https://geant4.web.cern.ch/support
# with the link text of `User Support`
# NOTE: both text and url can be empty
def autolinkToG4Page(pattern):
    def role(name, rawtext, text, lineno, inliner, options={}, content=[]):
        # get the sub-url and text parts of the enrty text (seprated by `,`)
        parts = text.split(",")
        url = pattern % (parts[0],)
        print(parts)
        node = nodes.reference(rawtext, parts[1], refuri=url, **options)
        return [node], []
    return role
