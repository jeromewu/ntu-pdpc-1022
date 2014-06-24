if &cp | set nocp | endif
nmap <silent> ,r :!./%
nmap <silent> ,xx :%!xxd -r
nmap <silent> ,x :%!xxd
nmap <silent> ,n :silent :nohlsearch
let s:cpo_save=&cpo
set cpo&vim
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set autoread
set background=dark
set backspace=indent,eol,start
set cindent
set completeopt=longest,menuone
set cscopeprg=/usr/bin/cscope
set cscopetag
set cscopeverbose
set expandtab
set fileencodings=ucs-bom,utf-8,latin1
set guicursor=n-v-c:block,o:hor50,i-ci:hor15,r-cr:hor30,sm:block,a:blinkon0
set helplang=en
set history=1000
set hlsearch
set ignorecase
set incsearch
set laststatus=2
set ruler
set rulerformat=%30(%=:b%n%y%m%r%w\ %l,%c%V\ %P%)
set shiftwidth=2
set smartcase
set softtabstop=2
set statusline=\ %{HasPaste()}%F%m%r%h\ %w\ \ CWD:\ %r%{getcwd()}%h\ \ \ Line:\ %l
set tabstop=2
set title
set viminfo=%,'100,<50,s10,h
set visualbell
set wildignore=*.o,*~,*.pyc
set wildmenu
set wildmode=longest:full:list
" vim: set ft=vim :
