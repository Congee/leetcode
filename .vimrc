set secure

function! SwitchBetweenSourceTest()
    if expand("%:e") == "dat"
        let l:to = expand("%:p")[:-11] . ".cpp"  " .tests.dat
    else
        let l:to = expand("%:p:r") . ".tests.dat"
    endif

    " multiple buffers may share one window
    " if l:to->buflisted()
    "     silent! execute bufwinnr(bufname(l:to)) . "wincmd w"
    " elseif filereadable(l:to)
    "     silent! execute ":edit " . l:to
    " endif

    silent! execute ":edit " . l:to
endfunction

command! -nargs=0 A :call SwitchBetweenSourceTest()
